/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:03:58 by ecross            #+#    #+#             */
/*   Updated: 2020/02/08 17:44:13 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/********
   window and image functions
********/

int put_image(void *win_struct)
{
	window_struct *ws;

	ws = win_struct;
	mlx_put_image_to_window(ws->mlx_ptr, ws->win_ptr, ws->img_ptr, 0, 0);
	return (0);
}

int set_keys(int keycode, void *win_struct)
{
	window_struct *ws;

	ws = win_struct;
	if (keycode == 53)
	{
		mlx_destroy_window(ws->mlx_ptr, ws->win_ptr);
		exit(0);
	}
	if (keycode == 8)
		mlx_clear_window(ws->mlx_ptr, ws->win_ptr);
	return (0);
}

int close_program(void *win_struct)
{
	exit(0);
}

int put_pixel(void *win_struct)
{
	window_struct *ws;
	
	ws = win_struct;
	mlx_pixel_put(ws->mlx_ptr, ws->win_ptr, ws->res_x / 2, ws->res_y / 2, 0xff00ff);
	return (0);
}

int initialise_window(window_struct *ws)
{
	ws->mlx_ptr = mlx_init();
	ws->win_ptr = mlx_new_window(ws->mlx_ptr, ws->res_x, ws->res_y, "window");
	if (!ws->win_ptr)	/*need to initialise struct values*/
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

float	calc_dot_prod(double *vec1, double *vec2)
{
	return ((vec1[0] * vec2[0]) + (vec1[1] * vec2[1]) + (vec1[2] * vec2[2]));
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

	mag = calc_vector_mag(vec);;
	unit_vec[0] = vec[0] / mag;
	unit_vec[1] = vec[1] / mag;
	unit_vec[2] = vec[2] / mag;
}

double	calc_light_intensity(double *ray_vec, scene_struct *s, double t_min)
{
	/*compute surface point coordinates*/
	/*cam pos + t_min(unit ray vector)*/

	double	dot;
	double	fraction;
	double	ray_unit_vec[3];
	double	obj_surface_xyz[3];
	double	surface_to_light_vec[3];
	double	obj_norm_vec[3];
	
	calc_unit_vec(ray_vec, ray_unit_vec);
	obj_surface_xyz[X] = s->cam_xyz[X] + (t_min * ray_unit_vec[X]);
	obj_surface_xyz[Y] = s->cam_xyz[Y] + (t_min * ray_unit_vec[Y]);
	obj_surface_xyz[Z] = s->cam_xyz[Z] + (t_min * ray_unit_vec[Z]);

	/*compute vector from surface pos to light*/

	calc_3d_vector(obj_surface_xyz, s->light_xyz, surface_to_light_vec);

	/*compute surface normal (normalised) - need identifier of which object - use function array*/
	/*here using sphere so normal is just vector between center and surface point*/
	/*normal calculation functions should always give a normalised vector*/
	
	calc_3d_vector(s->sphere_xyz, obj_surface_xyz, obj_norm_vec);
	calc_unit_vec(obj_norm_vec, obj_norm_vec);
	
	/*compute dot product of normal and light ray*/
	/*if the dot product is negative, means angle between vectors of more than 90, which
	  means light source is behind the point - so no illumination*/

	if ((dot = calc_dot_prod(surface_to_light_vec, obj_norm_vec)) < 0)
		return (0);

	/*compute intensity from spot light*/
	fraction = dot / (calc_vector_mag(surface_to_light_vec) * calc_vector_mag(obj_norm_vec));
	
	/*return this fraction of spot light intensity plus ambient light intensity*/
	return (s->light_brightness * fraction);
}

double	solve_quadratic(double *cam_xyz, double *ray_vec, double *sphere_xyz, double sphere_diameter)
{
	double	sphere_to_cam_vec[3];
	double	a;
	double	b;
	double	c;
	double	r;
	double	discriminant;
	double	smallest_root;

	calc_3d_vector(sphere_xyz, cam_xyz, sphere_to_cam_vec);
	r = sphere_diameter / 2;
	a = calc_dot_prod(ray_vec, ray_vec);
	b = 2 * calc_dot_prod(sphere_to_cam_vec, ray_vec);
	c = calc_dot_prod(sphere_to_cam_vec, sphere_to_cam_vec) - (r * r);
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (INFINITY);
	smallest_root = ((-1 * b) + sqrt(discriminant)) / (2 * a);
	if (((-1 * b) - sqrt(discriminant)) / (2 * a) < smallest_root)
		smallest_root = ((-1 * b) - sqrt(discriminant)) / (2 * a);
	return (smallest_root);
}

/********
   main
********/

int main(void)
{
	int		x;
	int		y;
	int		bpp;
	int		line_size;
	int		endian;
	int		pixel_colour[3];
	char	*img_addr;
	double	distance_to_viewport;
	double	viewport_width;
	double	viewport_height;
	double	viewport_pix_xyz[3];
	double	ray_vec[3];
	double	intersect_dist_max;
	double	intersect_dist_min;
	double	t_min;
	double	scale;
	scene_struct s;
	window_struct ws;

	/*
	  section to be replaced by the parser
	*/

	distance_to_viewport = 1;
	s.res_xy[X] = 1000;
	s.res_xy[Y] = 625;
	
	s.cam_xyz[X] = 0;
	s.cam_xyz[Y] = 0;
	s.cam_xyz[Z] = 0;
	s.cam_fov = 60;
	
	s.ambient_ratio = 0.2;
	s.ambient_colour[X] = 0;
	s.ambient_colour[Y] = 0;
	s.ambient_colour[Z] = 0;

	s.light_xyz[X] = 50;
	s.light_xyz[Y] = 30;
	s.light_xyz[Z] = 50;
	s.light_brightness = 0.5;
	s.light_colour[X] = 255;
	s.light_colour[Y] = 255;
	s.light_colour[Z] = 255;
	
	s.sphere_xyz[X] = 0;
	s.sphere_xyz[Y] = 0;
	s.sphere_xyz[Z] = 40;
	s.sphere_diameter = 10;
	s.sphere_colour[R] = 100; 
	s.sphere_colour[G] = 200; 
	s.sphere_colour[B] = 100;

	/*
	  set values needed for ray tracing
	*/

	viewport_width = (2 * tan((s.cam_fov * (M_PI / 180)) / 2) * distance_to_viewport);	/*calc vp width using horizontal FOV*/
	viewport_height = s.res_xy[Y] * (viewport_width / s.res_xy[X]);						/*calc vp height using screen res ratio*/
	intersect_dist_max = 100000;
	intersect_dist_min = distance_to_viewport;

	/*
	  set up window and create image for ray tracing
	*/

	ws.res_x = s.res_xy[X];
	ws.res_y = s.res_xy[Y];
	initialise_window(&ws);
	/*for each cam struct in cam list*/
	ws.img_ptr = mlx_new_image(ws.mlx_ptr, ws.res_x, ws.res_y);
	img_addr = mlx_get_data_addr(ws.img_ptr, &bpp, &line_size, &endian);
	
	/*
	  function to scale the light intensity of each light source
	  so that total light intensity is always 1.0
	*/

	scale = 1 / (s.ambient_ratio + s.light_brightness);
	s.ambient_ratio *= scale;
	s.light_brightness *= scale;

	/*
	  ray tracing algorithm
	*/

	pixel_colour[R] = 0;
	pixel_colour[G] = 0;
	pixel_colour[B] = 0;
	t_min = INFINITY;
	ray_vec[Z] = distance_to_viewport;
	x = 0;
	while (x < s.res_xy[X])
	{
		y = 0;
		while (y < s.res_xy[Y])
		{
			ray_vec[X] = (viewport_width * ((double)x / s.res_xy[X])) - (viewport_width / 2);
			ray_vec[Y] = (-1 * viewport_height * ((double)y / s.res_xy[Y])) + (viewport_height / 2);
			/*for each object in object list - find t_min, if this is the smallest found so far
			  store it in t_min var and keep track of which object this was*/
			t_min = solve_quadratic(s.cam_xyz, ray_vec, s.sphere_xyz, s.sphere_diameter);
			if (t_min == INFINITY)
				colour_img_pixel(img_addr, x, y, bpp, line_size, s.ambient_colour);
			else
			{
				/*do lots of stuff to get correct colour - using t_min and the object which gave it*/
				pixel_colour[G] = (double)255 * (s.ambient_ratio + calc_light_intensity(ray_vec, &s, t_min));
				pixel_colour[R] = (double)255 * (s.ambient_ratio + calc_light_intensity(ray_vec, &s, t_min));
				colour_img_pixel(img_addr, x, y, bpp, line_size, pixel_colour);
			}
			y++;
		}
		x++;
	}
	
	/*
	  run loop
	*/

	mlx_loop(ws.mlx_ptr);
}
