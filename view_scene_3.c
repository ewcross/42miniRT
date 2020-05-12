/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_scene_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 18:15:54 by ecross            #+#    #+#             */
/*   Updated: 2020/05/12 18:32:01 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	adj_cl(int *res_colour, t_obj_struct *obj, int *l_colour,
							double intensity)
{
	double	x;
	int		*obj_colour;

	obj_colour = obj->colour;
	x = 1 / (1 + intensity);
	res_colour[R] = (obj_colour[R] * x) + (l_colour[R] * x * intensity);
	res_colour[G] = (obj_colour[G] * x) + (l_colour[G] * x * intensity);
	res_colour[B] = (obj_colour[B] * x) + (l_colour[B] * x * intensity);
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
