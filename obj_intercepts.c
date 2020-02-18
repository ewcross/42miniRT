/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intercepts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:48:54 by ecross            #+#    #+#             */
/*   Updated: 2020/02/18 18:21:57 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "structs.h"

int	plane_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
					t_obj_struct *pl)
{
	double	ray_normal_dot;
	double	plane_to_cam_vec[3];

	calc_3d_vector(ray_orig_xyz, pl->xyz, plane_to_cam_vec);
	ray_normal_dot = calc_dot_prod(ray_vec, pl->normal);
	if (!ray_normal_dot)
	{
		*t_min = INFINITY;
		return (0);
	}
	*t_min = calc_dot_prod(plane_to_cam_vec, pl->normal) / ray_normal_dot;
	return (1);
}

int	solve_quadratic(double *t_min, double *ray_vec, double *ray_orig_xyz,
					t_obj_struct *sp)
{
	double	sphere_to_cam_vec[3];
	double	a;
	double	b;
	double	c;
	double	r;
	double	discriminant;
	double	smallest_root;

	calc_3d_vector(sp->xyz, ray_orig_xyz, sphere_to_cam_vec);
	r = sp->data.doubl / 2;
	a = calc_dot_prod(ray_vec, ray_vec);
	/*maybe see here if using a normlised ray vector makes a difference*/
	b = 2 * calc_dot_prod(sphere_to_cam_vec, ray_vec);
	c = calc_dot_prod(sphere_to_cam_vec, sphere_to_cam_vec) - (r * r);
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
	{
		*t_min = INFINITY;
		return (0);
	}
	smallest_root = ((-1 * b) + sqrt(discriminant)) / (2 * a);
	if (((-1 * b) - sqrt(discriminant)) / (2 * a) < smallest_root)
		smallest_root = ((-1 * b) - sqrt(discriminant)) / (2 * a);
	*t_min = smallest_root;
	return (1);
}

int	sq_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
				t_obj_struct *pl)
{
	*t_min = INFINITY;
	return (0);
}

int	tr_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
				t_obj_struct *pl)
{
	*t_min = INFINITY;
	return (0);
}

int	cy_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
				t_obj_struct *pl)
{
	*t_min = INFINITY;
	return (0);
}
