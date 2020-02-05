/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:03:58 by ecross            #+#    #+#             */
/*   Updated: 2020/02/05 10:41:58 by ecross           ###   ########.fr       */
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

	distance_to_viewport = 1;
	s.cam_xyz[X] = 0;
	s.cam_xyz[Y] = 0;
	s.cam_xyz[Z] = 0;
	s.cam_fov = 60;
	s.res_xy[X] = 1920;
	s.res_xy[Y] = 1080;

	s.sphere_xyz[X] = 0;
	s.sphere_xyz[Y] = 0;
	s.sphere_xyz[Z] = 20;
	s.sphere_diameter = 12.5;

	viewport_width = (2 * tan((s.cam_fov * (M_PI / 180)) / 2) * distance_to_viewport);	/*calc vp width using horizontal FOV*/
	printf("viewport_width = %f\n", viewport_width);
	viewport_height = s.res_xy[Y] * (viewport_width / s.res_xy[X]);						/*calc vp height using screen res ratio*/
	printf("viewport_height = %f\n", viewport_height);

	intersect_dist_max = 100000;
	intersect_dist_min = distance_to_viewport;
	ray_vector[Z] = distance_to_viewport;												/*set ray vector z to distance of vp from camera*/
	//x = (s.res_xy[X] / 2) * -1;															/*min x value is negative half the canvas width*/
	//while (x < s.res_xy[X] / 2)															/*max x value is positive half the canvas width*/
	x = -10;
	while (x < -9)
	{																					/*as Z+ is being used as vp normal, vp is in xy plane*/
		//y = (s.res_xy[Y] / 2) * -1;														/*so half must be -x and half +x, and same for y*/
		//while (y < s.res_xy[Y] / 2)
		y = -10;
		while (y < -9)
		{
			ray_vector[X] = viewport_width * (x / s.res_xy[X]);							/*set ray vector x using ratio of x pixel pos to canvas width*/
			ray_vector[Y] = viewport_height * (y / s.res_xy[Y]);						/*same for y*/
			/*here need to apply cam_normal to ray_vector to rotate the vector*/
			/*then for each sphere in scene, and for any other shapes*/
			solve_quadratic(p1p2, s.cam_xyz, ray_vector, s.sphere_xyz, s.sphere_diameter);
			printf("root 1 = %f\n", p1p2[0]);
			printf("root 2 = %f\n", p1p2[1]);
			y++;
		}
		x++;
	}
}
