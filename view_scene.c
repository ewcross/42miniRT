/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:03:58 by ecross            #+#    #+#             */
/*   Updated: 2020/02/08 12:43:10 by ecross           ###   ########.fr       */
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

double	calc_light_intensity()
{
	/*
	  compute t_min coordinates
	  compute vector from t_min to light
	  compute sphere surface normal
	  compute dot product of normal and light ray
	  compute intensity from spot light
	  add to ambient intensity
	  return overall intensity value
	 */
}

double	solve_quadratic(double *cam_xyz, double *ray_vector, double *sphere_xyz, double sphere_diameter)
{
	double	sphere_to_cam_vector[3];
	double	a;
	double	b;
	double	c;
	double	r;
	double	discriminant;
	double	smallest_root;

	calc_3d_vector(sphere_xyz, cam_xyz, sphere_to_cam_vector);
	r = sphere_diameter / 2;
	a = calc_dot_prod(ray_vector, ray_vector);
	b = 2 * calc_dot_prod(sphere_to_cam_vector, ray_vector);
	c = calc_dot_prod(sphere_to_cam_vector, sphere_to_cam_vector) - (r * r);
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
	double	ray_vector[3];
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

	s.light_xyz[X] = 0;
	s.light_xyz[Y] = 0;
	s.light_xyz[Z] = 0;
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

	pixel_colour[R] = 255;
	pixel_colour[G] = 120;
	pixel_colour[B] = 100;
	t_min = INFINITY;
	ray_vector[Z] = distance_to_viewport;
	x = 0;
	while (x < s.res_xy[X])
	{
		y = 0;
		while (y < s.res_xy[Y])
		{
			ray_vector[X] = (viewport_width * ((double)x / s.res_xy[X])) - (viewport_width / 2);
			ray_vector[Y] = (-1 * viewport_height * ((double)y / s.res_xy[Y])) + (viewport_height / 2);
			/*for each object in object list - find t_min, if this is the smallest found so far
			  store it in t_min var and keep track of which object this was*/
			t_min = solve_quadratic(s.cam_xyz, ray_vector, s.sphere_xyz, s.sphere_diameter);
			if (t_min == INFINITY)
				colour_img_pixel(img_addr, x, y, bpp, line_size, s.ambient_colour);
			else
			{
				/*do lots of stuff to get correct colour - using t_min and the object which gave it*/
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
