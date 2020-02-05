/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:03:58 by ecross            #+#    #+#             */
/*   Updated: 2020/02/05 12:48:28 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_vec(double *vec)
{
	printf("(%f, %f, %f)\n", vec[X], vec[Y], vec[Z]);
}

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

void	solve_quadratic(double *p1p2, double *cam_xyz, double *ray_vector, double *sphere_xyz, double sphere_diameter)
{
	double	sphere_to_cam_vector[3];
	double	a;
	double	b;
	double	c;
	double	r;
	double	discriminant;

	calc_3d_vector(sphere_xyz, cam_xyz, sphere_to_cam_vector);
	r = sphere_diameter / 2;
	a = calc_dot_prod(ray_vector, ray_vector);
	b = 2 * calc_dot_prod(sphere_to_cam_vector, ray_vector);
	c = calc_dot_prod(sphere_to_cam_vector, sphere_to_cam_vector) - (r * r);
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		p1p2[0] = p1p2[1] = INFINITY;
	else
	{
		p1p2[0] = ((-1 * b) + sqrt(discriminant)) / (2 * a);
		p1p2[1] = ((-1 * b) - sqrt(discriminant)) / (2 * a);
	}
}

int put_image(void *win_struct)
{
	window_struct *ws;

	ws = win_struct;
	mlx_put_image_to_window(ws->mlx_ptr, ws->win_ptr, ws->img_ptr, ws->res_x / 2, ws->res_y / 2);
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

/*probably put the image info in a struct*/

void	colour_img_pixel(char *img_addr, int x, int y, int bpp, int line_size, int *colour)
{
	int	pixel_index;
	int max;

	max = 255;
	pixel_index = x + ((bpp / 8) * line_size * y);
	*(img_addr + pixel_index + 1) = colour[R];
	*(img_addr + pixel_index + 2) = colour[G];
	*(img_addr + pixel_index + 3) = colour[B];
	/*colour random pixel to test*/
	*img_addr = 0;
	*(img_addr + 41) = max;
	*(img_addr + 42) = 0;
	*(img_addr + 43) = 0;
}

int initialise_window(window_struct *ws)
{
	/*initialisation of connection, creation of window and hooks*/
	ws->mlx_ptr = mlx_init();
	ws->win_ptr = mlx_new_window(ws->mlx_ptr, ws->res_x, ws->res_y, "window");
	if (!ws->win_ptr)	/*need to initialise struct values*/
		return (1);
	mlx_hook(ws->win_ptr, DESTROYNOTIFY, NOEVENTMASK, close_program, 0);
	mlx_key_hook(ws->win_ptr, set_keys, ws);
	mlx_loop_hook(ws->mlx_ptr, put_image, ws);
	//mlx_loop_hook(ws->mlx_ptr, put_pixel, ws);
	/*creation of image with same size as window*/	
	ws->img_ptr = mlx_new_image(ws->mlx_ptr, ws->res_x, ws->res_y);
	/*create image contents*/
	
	return (0);
}

int main(void)
{
	int		x;
	int		y;
	double	distance_to_viewport;
	double	viewport_width;
	double	viewport_height;
	double	viewport_pix_xyz[3];
	double	ray_vector[3];
	double	intersect_dist_max;
	double	intersect_dist_min;
	double	p1p2[2];
	scene_struct s;
	window_struct ws;

	/*
	  section to be replaced by the parser
	*/

	distance_to_viewport = 1;
	s.cam_xyz[X] = 0;
	s.cam_xyz[Y] = 0;
	s.cam_xyz[Z] = 0;
	s.cam_fov = 60;
	s.res_xy[X] = 1000;
	s.res_xy[Y] = 625;
	s.ambient_colour[X] = 100;
	s.ambient_colour[Y] = 100;
	s.ambient_colour[Z] = 100;

	s.sphere_xyz[X] = 0;
	s.sphere_xyz[Y] = 0;
	s.sphere_xyz[Z] = 20;
	s.sphere_diameter = 12.5;
	s.sphere_colour[R] = 255; 
	s.sphere_colour[G] = 0; 
	s.sphere_colour[B] = 255;

	/*
	  set values needed for ray tracing
	*/

	viewport_width = (2 * tan((s.cam_fov * (M_PI / 180)) / 2) * distance_to_viewport);	/*calc vp width using horizontal FOV*/
	printf("viewport_width = %f\n", viewport_width);
	viewport_height = s.res_xy[Y] * (viewport_width / s.res_xy[X]);						/*calc vp height using screen res ratio*/
	printf("viewport_height = %f\n", viewport_height);

	intersect_dist_max = 100000;
	intersect_dist_min = distance_to_viewport;

	/*
	  set up window and create image for ray tracing
	*/

	ws.res_x = s.res_xy[X];
	ws.res_y = s.res_xy[Y];
	initialise_window(&ws);
	/*get img_addr and values needed by pixel_colouring function*/
	char	*img_addr;
	int		bpp;
	int		line_size;
	int		endian;

	img_addr = mlx_get_data_addr(ws.img_ptr, &bpp, &line_size, &endian);

	/*
	  ray tracing algorithm
	*/

	ray_vector[Z] = distance_to_viewport;												/*set ray vector z to distance of vp from camera*/
	//x = (s.res_xy[X] / 2) * -1;															/*min x value is negative half the canvas width*/
	//while (x < s.res_xy[X] / 2)															/*max x value is positive half the canvas width*/
	x = 0;
	while (x < 1)
	{																					/*as Z+ is being used as vp normal, vp is in xy plane*/
		//y = (s.res_xy[Y] / 2) * -1;														/*so half must be -x and half +x, and same for y*/
		//while (y < s.res_xy[Y] / 2)
		y = 0;
		while (y < 1)
		{
			ray_vector[X] = viewport_width * (x / s.res_xy[X]);							/*set ray vector x using ratio of x pixel pos to canvas width*/
			ray_vector[Y] = viewport_height * (y / s.res_xy[Y]);						/*same for y*/
			/*here need to apply cam_normal to ray_vector to rotate the vector*/
			/*then for each sphere in scene, and for any other shapes*/
			solve_quadratic(p1p2, s.cam_xyz, ray_vector, s.sphere_xyz, s.sphere_diameter);
			if (p1p2[0] == INFINITY && p1p2[1] == INFINITY)
				colour_img_pixel(img_addr, x, y, bpp, line_size, s.ambient_colour);
			else
				colour_img_pixel(img_addr, x, y, bpp, line_size, s.sphere_colour);
			y++;
		}
		x++;
	}
	
	/*
	  run loop
	*/

	mlx_loop(ws.mlx_ptr);
}
