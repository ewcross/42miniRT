/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:03:58 by ecross            #+#    #+#             */
/*   Updated: 2020/02/25 15:48:49 by ecross           ###   ########.fr       */
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

void	scale_ints_vector(int *vec, double factor)
{
	vec[X] *= factor;
	vec[Y] *= factor;
	vec[Z] *= factor;
}

void	scale_vector(double *vec, double factor)
{
	vec[X] *= factor;
	vec[Y] *= factor;
	vec[Z] *= factor;
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
		scale_vector(obj_norm, -1);
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
	return (s->l_curr->brightness * dot_prod);
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
		if (temp_t_min < *t_min && temp_t_min > s->viewport_distance)
		{
			*t_min = temp_t_min;
			closest_obj = obj;
		}
		obj = obj->next;
	}
	return (closest_obj);
}


void	adjust_pixel_colour(int *colour, t_scene_struct *s, t_l_struct *light)
{
	double	l_brightness;
	double	a_brightness;

	l_brightness = light->brightness;
	a_brightness = s->ambient_ratio;
	colour[R] += l_brightness * light->colour[R];
	colour[G] += l_brightness * light->colour[G];
	colour[B] += l_brightness * light->colour[B];
	colour[R] += a_brightness * s->ambient_colour[R];
	colour[G] += a_brightness * s->ambient_colour[G];
	colour[B] += a_brightness * s->ambient_colour[B];
	if (colour[R] > 255)
		colour[R] = 255;
	if (colour[G] > 255)
		colour[G] = 255;
	if (colour[B] > 255)
		colour[B] = 255;
}

void	get_ray_vec(double *ray_vec, double *v_w_h, int *xy, t_scene_struct *s)
{
	ray_vec[X] = (v_w_h[0] * ((double)xy[X] / s->res_xy[X])) - (v_w_h[0] / 2);
	ray_vec[Y] = (-1 * v_w_h[1] * ((double)xy[Y] / s->res_xy[Y])) + (v_w_h[1] / 2);
	calc_unit_vec(ray_vec, ray_vec);
}

int trace_rays(t_scene_struct *s, void *img_addr)
{
	int				xy[2];
	int				pixel_colour[3];
	int				colour_black[3];
	double			ray_vec[3];
	double			viewport_w_h[2];
	double			t_min;
	double			light_adjust;
	t_l_struct		*light;
	t_obj_struct	*closest_obj;

	colour_black[R] = 0;
	colour_black[G] = 0;
	colour_black[B] = 0;

	scale_light(s);
	viewport_w_h[0] = (2 * tan((s->cam_curr->fov * (M_PI / 180)) / 2) * s->viewport_distance);
	viewport_w_h[1] = s->res_xy[Y] * (viewport_w_h[0] / s->res_xy[X]);
	closest_obj = NULL;
	ray_vec[Z] = s->viewport_distance;
	xy[X] = 0;
	while (xy[X] < s->res_xy[X])
	{
		xy[Y] = 0;
		while (xy[Y] < s->res_xy[Y])
		{
			get_ray_vec(ray_vec, viewport_w_h, xy, s);
			closest_obj = find_closest_obj(&t_min, s, ray_vec);
			if (t_min == INFINITY)
				colour_img_pixel(img_addr, xy, s->cam_curr, colour_black);
			else
			{
				//get_pixel_colour();
				fill_ints(closest_obj->colour, pixel_colour, 3);
				light_adjust = s->ambient_ratio;
				light = s->l_list;
				while(light)
				{
					s->l_curr = light;
					light_adjust += calc_light_intensity(s, closest_obj, ray_vec, t_min);
					//adjust_pixel_colour(pixel_colour, s, light);
					light = light->next;
				}
				scale_ints_vector(pixel_colour, light_adjust);
				colour_img_pixel(img_addr, xy, s->cam_curr, pixel_colour);
			}
			xy[Y]++;
		}
		xy[X]++;
	}
	return (0);
}

void	add_img_to_list(t_win_struct *ws, void	*img_ptr)
{
	t_img_struct	*elem;
	t_img_struct	*img_list;

	elem = (t_img_struct*)malloc(sizeof(t_img_struct));
	elem->img_ptr = img_ptr;
	elem->next = NULL;
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

int		main(int argc, char **argv)
{
	//int				hello[] = {1, 2, 3};
	void			*img_ptr;
	t_scene_struct	s;
	t_win_struct	ws;
	t_cam_struct	*cam;

	if (argc < 2 || argc > 3)
	{
		printf("Incorrect args supplied\n");
		return (1);
	}
	s.obj_list = NULL;
	s.viewport_distance = 1;
	/*need to initialise scene struct*/
	
	if(!parser(&s, argv[1]))
	{
		free_scene_struct(&s);
		return (1);
	}

	init_win_struct(&ws);
	ws.res_x = s.res_xy[X];
	ws.res_y = s.res_xy[Y];
	if (!initialise_window(&ws))
	{
		ft_putstr_fd("Failed to initialise window\n", 1);
		return (0);
	}

	cam = s.cam_list;
	while(cam)
	{
		img_ptr = mlx_new_image(ws.mlx_ptr, ws.res_x, ws.res_y);
		s.cam_curr = cam;
		trace_rays(&s, get_img_data(img_ptr, cam));
		add_img_to_list(&ws, img_ptr); 
		cam = cam->next;
	}
	mlx_loop(ws.mlx_ptr);
	free_img_list(ws.img_list);
	free_scene_struct(&s);
}
