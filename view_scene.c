/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:03:58 by ecross            #+#    #+#             */
/*   Updated: 2020/03/05 17:44:27 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "structs.h"

/********
   maths functions
********/

double	dot(double *vec1, double *vec2)
{
	return ((vec1[0] * vec2[0]) + (vec1[1] * vec2[1]) + (vec1[2] * vec2[2]));
}

void	cross(double *vec1, double *vec2, double *res)
{
	res[X] = (vec1[Y] * vec2[Z]) - (vec1[Z] * vec2[Y]);
	res[Y] = (vec1[Z] * vec2[X]) - (vec1[X] * vec2[Z]);
	res[Z] = (vec1[X] * vec2[Y]) - (vec1[Y] * vec2[X]);
}

void	scale_ints_vector(int *vec, double factor, int *res)
{
	res[X] = vec[X] * factor;
	res[Y] = vec[Y] * factor;
	res[Z] = vec[Z] * factor;
}

void	scale_vector(double *vec, double factor, double *res)
{
	res[X] = vec[X] * factor;
	res[Y] = vec[Y] * factor;
	res[Z] = vec[Z] * factor;
}

void	calc_3d_vector(double *start, double *end, double *res)
{
	res[0] = end[0] - start[0];
	res[1] = end[1] - start[1];
	res[2] = end[2] - start[2];
}

double	calc_vector_mag(double *vec)
{
	return(sqrt((vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2])));
}

double	calc_ints_vector_mag(int *vec)
{
	return(sqrt((vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2])));
}

void	calc_unit_ints_vec(int *vec, int *unit_vec)
{
	double mag;

	mag = calc_ints_vector_mag(vec);
	printf("mag %f\n", mag);
	if (mag == 0)
		mag = 1;
	unit_vec[0] = vec[0] / mag;
	unit_vec[1] = vec[1] / mag;
	unit_vec[2] = vec[2] / mag;
}

void	calc_unit_vec(double *vec, double *unit_vec)
{
	double mag;

	mag = calc_vector_mag(vec);
	if (mag == 0)
		return ;
	unit_vec[0] = vec[0] / mag;
	unit_vec[1] = vec[1] / mag;
	unit_vec[2] = vec[2] / mag;
}

void	get_point(double *point, double *orig, double *vec, double dist)
{
	point[X] = orig[X] + (dist * vec[X]);
	point[Y] = orig[Y] + (dist * vec[Y]);
	point[Z] = orig[Z] + (dist * vec[Z]);
}

void	scale_light(t_scene_struct *s)
{
	double		light_total;
	double		scale;
	t_l_struct	*light;

	light_total = 0;
	light = s->l_list;
	while (light)
	{
		light_total += light->brightness;
		light = light->next;
	}
	scale = 1 / (s->ambient_ratio + light_total);
	s->ambient_ratio *= scale;
	light = s->l_list;
	while (light)
	{
		light->brightness *= scale;
		light = light->next;
	}
}

int		shadow_ray(double *surface_xyz, double *light_vec, t_obj_struct *obj, t_obj_struct *obj_list)
{
	double	t_min;
	double	light_unit_vec[3];

	calc_unit_vec(light_vec, light_unit_vec);
	t_min = INFINITY;
	while (obj_list)
	{
		if (obj_list == obj)
		{
			obj_list = obj_list->next;
			continue;
		}
		/*need more conditions here for other cases*/
		/*might need to normalise vector first to test mag*/
		if (obj_list->solve(&t_min, light_unit_vec, surface_xyz, obj_list) && t_min > 0 && t_min < calc_vector_mag(light_vec))
			return (1);
		obj_list = obj_list->next;
	}
	return(0);
}

void	choose_correct_normal(double *cam_xyz, double *obj_xyz, double *obj_norm)
{
	double	mag1;
	double	mag2;
	double	dot_prod;
	double	cam_to_plane_vec[3];

	calc_3d_vector(cam_xyz, obj_xyz, cam_to_plane_vec);
	dot_prod = dot(cam_to_plane_vec, obj_norm);
	mag1 = calc_vector_mag(cam_to_plane_vec);
	mag2 = calc_vector_mag(obj_norm);
	if ((dot_prod / mag1 * mag2) > cos(M_PI / 2))
		scale_vector(obj_norm, -1, obj_norm);
}

double	calc_light_intensity(t_scene_struct *s, t_obj_struct *obj, double *ray_vec, double t_min)
{
	double	dot_prod;
	double	ray_unit_vec[3];
	double	obj_surface_xyz[3];
	double	surface_to_light_vec[3];
	double	obj_norm_vec[3];

	get_point(obj_surface_xyz, s->cam_curr->xyz, ray_vec, t_min);
	calc_3d_vector(obj_surface_xyz, s->l_curr->xyz, surface_to_light_vec);
	if (shadow_ray(obj_surface_xyz, surface_to_light_vec, obj, s->obj_list))
		return (0);
	obj->get_norm(obj_surface_xyz, obj, obj_norm_vec);
	if (obj->id != 's')
		choose_correct_normal(s->cam_curr->xyz, obj->xyz, obj_norm_vec);
	if ((dot_prod = dot(surface_to_light_vec, obj_norm_vec)) < 0)
		return (0);
	dot_prod /= (calc_vector_mag(surface_to_light_vec) * calc_vector_mag(obj_norm_vec));
	return (dot_prod);
}

t_obj_struct	*get_next_elem(t_obj_struct *start, char id)
{
	if (!start)
		return (start);
	start = start->next;
	while (start)
	{
		if (start->id == id)
			return (start);
		start = start->next;
	}
	return (start);
}

t_obj_struct	*find_closest_obj(double *t_min, t_scene_struct *s, double *ray_vec)
{
	double			temp_t_min;
	t_obj_struct	*obj;
	t_obj_struct	*closest_obj;

	closest_obj = NULL;
	*t_min = INFINITY;
	obj = s->obj_list;
	while (obj)
	{
		obj->solve(&temp_t_min, ray_vec, s->cam_curr->xyz, obj);
		if (temp_t_min < *t_min && temp_t_min > s->vp_dist)
		{
			*t_min = temp_t_min;
			closest_obj = obj;
		}
		obj = obj->next;
	}
	return (closest_obj);
}


void	adjust_pix_colour(int *res_colour, t_obj_struct *obj, int *light_colour, double intensity)
{
	double	x;
	int		*obj_colour;

	obj_colour = obj->colour;
	x = 1 / (1 + intensity);
	res_colour[R] = (obj_colour[R] * x) + (light_colour[R] * x * intensity);
	res_colour[G] = (obj_colour[G] * x) + (light_colour[G] * x * intensity);
	res_colour[B] = (obj_colour[B] * x) + (light_colour[B] * x * intensity);
}

void	rotate_about_x(double *ray, double *axis, int rev)
{
	double	d;
	double	y;
	double	z;

	y = ray[Y];
	z = ray[Z];
	d = sqrt((axis[Y] * axis[Y]) + (axis[Z] * axis[Z]));
	if (!d)
		return ;
	ray[Y] = ((axis[Z] / d) * y) + ((rev * -1 * (axis[Y] / d)) * z);
	ray[Z] = ((rev * (axis[Y] / d)) * y) + ((axis[Z] / d) * z);
}

void	rotate_about_y(double *ray, double *axis, int rev)
{
	double	d;
	double	x;
	double	z;

	x = ray[X];
	z = ray[Z];
	d = sqrt((axis[Y] * axis[Y]) + (axis[Z] * axis[Z]));
	ray[X] = (d * x) + (rev * -1 * axis[X] * z);
	ray[Z] = (rev * axis[X] * x) + (d * z);
}

void	rotate_about_z(double *ray, double angle)
{
	double x;
	double y;

	x = ray[X];
	y = ray[Y];
	ray[X] = (cos(angle) * x) - (sin(angle) * y);
	ray[Y] = (sin(angle) * x) + (cos(angle) * y);
}

void	rotate_ray(double *ray, t_cam_struct *cam)
{
	int		on;
	double	angle;
	double	*axis;

	axis = cam->rot_axis;
	angle = cam->rot_angle;
	if (angle == 0)
		return ;
	rotate_about_x(ray, axis, 1);
	rotate_about_y(ray, axis, 1);
	rotate_about_z(ray, angle);
	rotate_about_y(ray, axis, -1);
	rotate_about_x(ray, axis, -1);
}

void	get_ray_vec(double *ray_vec, double *v_w_h, int *xy, t_scene_struct *s)
{
	ray_vec[X] = (v_w_h[0] * ((double)xy[X] / s->res_xy[X])) - (v_w_h[0] / 2);
	ray_vec[Y] = (-1 * v_w_h[1] * ((double)xy[Y] / s->res_xy[Y])) + (v_w_h[1] / 2);
	calc_unit_vec(ray_vec, ray_vec);
	rotate_ray(ray_vec, s->cam_curr);
}

void	get_pixel_colour(t_scene_struct *s, t_ray_struct *ray)
{
	static int	black[] = {0, 0, 0};
	double		intensity;
	double		light_adjust;
	t_l_struct	*light;

	if (ray->t_min == INFINITY)
	{
		fill_ints(black, ray->colour, 3);
		return ;
	}
	fill_ints(ray->closest_obj->colour, ray->colour, 3);
	light_adjust = s->ambient_ratio;
	adjust_pix_colour(ray->colour, ray->closest_obj, s->ambient_colour, s->ambient_ratio);
	light = s->l_list;
	while(light)
	{
		s->l_curr = light;
		intensity = calc_light_intensity(s, ray->closest_obj, ray->ray_vec, ray->t_min);
		light_adjust += light->brightness * intensity;
		/*need to collect colour of all lights and then mix them all together in one*/
		adjust_pix_colour(ray->colour, ray->closest_obj, light->colour, intensity);
		light = light->next;
	}
	scale_ints_vector(ray->colour, light_adjust, ray->colour);
}

int	trace_rays(t_scene_struct *s, void *img_addr, double *vp_w_h)
{
	int				xy[2];
	t_ray_struct	ray;

	ray.closest_obj = NULL;
	xy[X] = 0;
	while (xy[X] < s->res_xy[X])
	{
		xy[Y] = 0;
		while (xy[Y] < s->res_xy[Y])
		{
			ray.ray_vec[Z] = 1;
			get_ray_vec(ray.ray_vec, vp_w_h, xy, s);
			ray.closest_obj = find_closest_obj(&(ray.t_min), s, ray.ray_vec);
			get_pixel_colour(s, &ray);
			colour_img_pixel(img_addr, xy, s->cam_curr, ray.colour);
			xy[Y]++;
		}
		xy[X]++;
	}
	return (0);
}

int	draw_image(t_scene_struct *s, void *img_addr)
{
	double			vp_w_h[2];

	scale_light(s);
	vp_w_h[0] = (2 * tan((s->cam_curr->fov * (M_PI / 180)) / 2) * s->vp_dist);
	vp_w_h[1] = s->res_xy[Y] * (vp_w_h[0] / s->res_xy[X]);
	trace_rays(s, img_addr, vp_w_h);
	return (0);
}

void	add_img_to_list(t_win_struct *ws, void *img_ptr, char *img_addr, t_cam_struct *cam)
{
	t_img_struct	*elem;
	t_img_struct	*img_list;

	elem = (t_img_struct*)malloc(sizeof(t_img_struct));
	elem->img_ptr = img_ptr;
	elem->img_addr = img_addr;
	elem->next = NULL;
	elem->bpp = cam->bpp;
	elem->line_size = cam->line_size;
	if (!ws->img_list)
	{
		ws->img_list = elem;
		ws->first_img_addr = elem;
		return ;
	}
	img_list = ws->img_list;
	while (img_list->next)
		img_list = img_list->next;
	img_list->next = elem;
}

void	*get_img_data(void *img_ptr, t_cam_struct *cam)
{
	int		bpp;
	int		ln;
	int		endian;
	void	*img_addr;

	img_addr = mlx_get_data_addr(img_ptr, &bpp, &ln, &endian);
	cam->bpp = bpp;
	cam->line_size = ln;
	return (img_addr);
}

int		str_match(char *str, char *real)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] != real[i])
			return (0);
		i++;
	}
	if (str[i] != real[i])
		return (0);
	return (1);
}

int		check_args(int argc, char **argv)
{
	if (argc < 2 || argc > 4)
	{
		ft_putstr_fd("Incorrect args supplied\n", 1);
		return (0);
	}
	if (argc == 3 && !str_match(argv[2], "--save"))
	{
		ft_putstr_fd("Invalid second argument.", 1);
		ft_putstr_fd(" Use '--save' to save image as bmp.\n", 1);
		return (0);
	}
	return (1);
}

void	create_image_list(t_win_struct *ws, t_scene_struct *s)
{
	void			*img_ptr;
	char			*img_addr;
	t_cam_struct	*cam;

	cam = s->cam_list;
	while(cam)
	{
		img_ptr = mlx_new_image(ws->mlx_ptr, ws->res_x, ws->res_y);
		s->cam_curr = cam;
		img_addr = get_img_data(img_ptr, cam);
		draw_image(s, img_addr);
		add_img_to_list(ws, img_ptr, img_addr, cam); 
		cam = cam->next;
	}
}

int		main(int argc, char **argv)
{
	//int			hello[] = {1, 2, 3};
	t_scene_struct	s;
	t_win_struct	ws;

	if(!check_args(argc, argv))
		return (1);
	/*here still using 1 as vp_distance*/
	init_scene_struct(&s, 1);
	if(!parser(&s, argv[1]))
	{
		free_scene_struct(&s);
		return (1);
	}
	init_win_struct(&ws, s.res_xy[X], s.res_xy[Y]);
	if (!initialise_window(&ws))
	{
		ft_putstr_fd("Failed to initialise window.\n", 1);
		return (1);
	}
	create_image_list(&ws, &s);
	if (argc == 2)
		mlx_loop(ws.mlx_ptr);
	else if (argc == 3)
		bmp(&ws, ws.img_list);
	free_img_list(ws.img_list);
	free_scene_struct(&s);
}
