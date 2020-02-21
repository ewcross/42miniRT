/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:03:58 by ecross            #+#    #+#             */
/*   Updated: 2020/02/21 13:57:13 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "structs.h"

/********
   window and image functions
********/

int put_image(void *window_struct)
{
	t_win_struct *ws;

	ws = window_struct;
	mlx_put_image_to_window(ws->mlx_ptr, ws->win_ptr, ws->img_ptr, 0, 0);
	return (0);
}

int set_keys(int keycode, void *window_struct)
{
	t_win_struct *ws;

	ws = window_struct;
	if (keycode == 53)
	{
		mlx_destroy_window(ws->mlx_ptr, ws->win_ptr);
		exit(0);
	}
	if (keycode == 8)
		mlx_clear_window(ws->mlx_ptr, ws->win_ptr);
	return (0);
}

int close_program(void *window_struct)
{
	(void)window_struct;
	exit(0);
}

int put_pixel(void *window_struct)
{
	t_win_struct *ws;
	
	ws = window_struct;
	mlx_pixel_put(ws->mlx_ptr, ws->win_ptr, ws->res_x / 2, ws->res_y / 2, 0xff00ff);
	return (0);
}

int initialise_window(t_win_struct *ws)
{
	ws->mlx_ptr = mlx_init();
	ws->win_ptr = mlx_new_window(ws->mlx_ptr, ws->res_x, ws->res_y, "window");
	if (!ws->win_ptr)
		return (1);
	mlx_hook(ws->win_ptr, DESTROYNOTIFY, NOEVENTMASK, close_program, 0);
	mlx_key_hook(ws->win_ptr, set_keys, ws);
	mlx_loop_hook(ws->mlx_ptr, put_image, ws);
	
	return (0);
}

void	colour_img_pixel(char *img_addr, int x, int y, int bpp, int line_size, int *colour)
{
	int	pixel_index;

	pixel_index = (x * (bpp / 8)) + ((line_size) * y);
	*(img_addr + pixel_index) = colour[B];
	*(img_addr + pixel_index + 1) = colour[G];
	*(img_addr + pixel_index + 2) = colour[R];
}

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
	{
		obj_norm[X] *= -1;
		obj_norm[Y] *= -1;
		obj_norm[Z] *= -1;
	}
}

double	calc_light_intensity(t_cam_struct *cam, t_l_struct *light, t_obj_struct *obj,
								t_obj_struct *obj_list, double *ray_vec, double t_min)
{
	double	dot_prod;
	double	fraction;
	double	ray_unit_vec[3];
	double	obj_surface_xyz[3];
	double	surface_to_light_vec[3];
	double	obj_norm_vec[3];

	/*find point on surface*/
	/*here assuming unit vec not used in ray tracing part*/
	//calc_unit_vec(ray_vec, ray_unit_vec);
	//obj_surface_xyz[X] = cam->xyz[X] + (t_min * ray_unit_vec[X]);
	//obj_surface_xyz[Y] = cam->xyz[Y] + (t_min * ray_unit_vec[Y]);
	//obj_surface_xyz[Z] = cam->xyz[Z] + (t_min * ray_unit_vec[Z]);

	/*here assuming ray vec is already a unit vector*/
	obj_surface_xyz[X] = cam->xyz[X] + (t_min * ray_vec[X]);
	obj_surface_xyz[Y] = cam->xyz[Y] + (t_min * ray_vec[Y]);
	obj_surface_xyz[Z] = cam->xyz[Z] + (t_min * ray_vec[Z]);
	
	/*find point to light vector*/
	calc_3d_vector(obj_surface_xyz, light->xyz, surface_to_light_vec);
	/*here need to check if it is a shadow ray*/
	/*if so, point gets no light from this light, so return 0*/
	if (shadow_ray(obj_surface_xyz, surface_to_light_vec, obj, obj_list))
		return (0);
	/*get normal to surface at that point*/
	obj->get_norm(obj_surface_xyz, obj, obj_norm_vec);
	if (obj->id != 's')
		choose_correct_normal(cam->xyz, obj->xyz, obj_norm_vec);
	/*get dot product of surface->light and normal*/
	/*if this is less than 0, angle is greater than 90, so it will be in shadow*/
	if ((dot_prod = dot(surface_to_light_vec, obj_norm_vec)) < 0)
		return (0);
	/*finally calculate fraction of light intensity that the point recieves*/
	fraction = dot_prod / (calc_vector_mag(surface_to_light_vec) * calc_vector_mag(obj_norm_vec));
	return (light->brightness * fraction);
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

int trace_rays(t_scene_struct *s, t_cam_struct *cam, void *img_addr, int line_size)
{
	int		x;
	int		y;
	int		pixel_colour[3];
	double	ray_vec[3];
	double	viewport_width;
	double	viewport_height;
	double	intersect_dist_max;
	double	intersect_dist_min;
	double	t_min;
	double	temp_t_min;
	double	light_adjust;
	
	t_l_struct		*light;
	t_l_struct		*first_light;
	t_obj_struct	*obj;
	t_obj_struct	*first_obj;
	t_obj_struct	*closest_obj;

	int		bpp = 32;
	
	/*
	  set values needed for ray tracing
	*/

	printf("res_x = %d\n", s->res_xy[X]);
	printf("res_y = %d\n", s->res_xy[Y]);
	viewport_width = (2 * tan((cam->fov * (M_PI / 180)) / 2) * s->viewport_distance);
	viewport_height = s->res_xy[Y] * (viewport_width / s->res_xy[X]);
	intersect_dist_max = 100000;
	intersect_dist_min = s->viewport_distance;

	/*
	  function to scale the light intensity of each light source
	  so that total light intensity is always 1.0
	*/

	scale_light(s);
	printf("\nscaled lights:\n\n");
	printf("a brightness = %f\n", s->ambient_ratio);
	light = s->l_list;
	while (light)
	{
		printf("\nbrightness = %f\n", light->brightness);
		light = light->next;
	}

	/*
	  ray tracing algorithm
	*/

	first_obj = s->obj_list;
	closest_obj = NULL;
	first_light = s->l_list;
	ray_vec[Z] = s->viewport_distance;
	x = 0;
	while (x < s->res_xy[X])
	{
		y = 0;
		while (y < s->res_xy[Y])
		{
			light_adjust = s->ambient_ratio;
			ray_vec[X] = (viewport_width * ((double)x / s->res_xy[X])) - (viewport_width / 2);
			ray_vec[Y] = (-1 * viewport_height * ((double)y / s->res_xy[Y])) + (viewport_height / 2);
			calc_unit_vec(ray_vec, ray_vec);
			t_min = INFINITY;
			obj = first_obj;
			while (obj)
			{
				obj->solve(&temp_t_min, ray_vec, cam->xyz, obj);
				if (temp_t_min < t_min && temp_t_min > s->viewport_distance)
				{
					t_min = temp_t_min;
					closest_obj = obj;
				}
				obj = obj->next;
			}
			if (t_min == INFINITY)
				colour_img_pixel(img_addr, x, y, bpp, line_size, s->ambient_colour);
			else
			{
				light = first_light;
				while(light)
				{
					light_adjust += calc_light_intensity(cam, light, closest_obj, s->obj_list, ray_vec, t_min);
					light = light->next;
				}
				pixel_colour[R] = (double)closest_obj->colour[R] * light_adjust;
				pixel_colour[G] = (double)closest_obj->colour[G] * light_adjust;
				pixel_colour[B] = (double)closest_obj->colour[B] * light_adjust;
				colour_img_pixel(img_addr, x, y, bpp, line_size, pixel_colour);
			}
			y++;
		}
		x++;
	}
	return (0);
}

int		main(void)
{
	/*
	  generate scene struct
	  use parser to fill with scene information
	  loop through obj structs and for each camera found, call ray tracer
	  also need to generate a new image for each camera found
	  ray tracer needs to be passed scene struct, camera struct and image address*/
	
	char			*file;
	void			*img_ptr;
	char			*img_addr;
	t_scene_struct	s;
	t_win_struct	ws;
	t_cam_struct	*cam;
	
	int		bpp;
	int		line_size;
	int		endian;

	file = "file.rt";
	init_win_struct(&ws);
	s.obj_list = NULL;
	s.viewport_distance = 1;
	/*need to initialise scene struct*/
	parser(&s, file);

	/*
	  set up window and create image for ray tracing
	*/

	ws.res_x = s.res_xy[X];
	ws.res_y = s.res_xy[Y];
	initialise_window(&ws);
	
	cam = s.cam_list;
	while(cam)
	{
		img_ptr = mlx_new_image(ws.mlx_ptr, ws.res_x, ws.res_y);
		img_addr = mlx_get_data_addr(img_ptr, &bpp, &line_size, &endian);
		trace_rays(&s, cam, img_addr, line_size);
		/*add new image to list of images in win_struct*/
		/*currently only one camera so just point ws.img_ptr to img_ptr*/
		ws.img_ptr = img_ptr;
		cam = cam->next;
	}
	mlx_loop(ws.mlx_ptr);
	/*free stuff*/
}
