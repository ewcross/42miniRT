/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intercepts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:48:54 by ecross            #+#    #+#             */
/*   Updated: 2020/02/20 15:11:27 by ecross           ###   ########.fr       */
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

	/*revisit using normalised vector here*/
	calc_3d_vector(sp->xyz, ray_orig_xyz, sphere_to_cam_vec);
	r = sp->data.doubl / 2;
	a = calc_dot_prod(ray_vec, ray_vec);
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

int		sq_solve(double *t_min, double *point, t_obj_struct *sq)
{
	double	dot;
	double	dummy_vec[3];
	double	ref_vec[3];
	double	point_vec[3];

	dummy_vec[X] = sq->normal[X] + 0.1;
	dummy_vec[Y] = sq->normal[Y];
	dummy_vec[Z] = sq->normal[Z];
	calc_cross_prod(sq->normal, dummy_vec, ref_vec);
	calc_unit_vec(ref_vec, ref_vec);
	scale_vector(ref_vec, sq->data.doubl);
	calc_3d_vector(sq->xyz, point, point_vec);
	dot = calc_dot_prod(ref_vec, point_vec);
	/*printf("------\n");
	printf("normal: %f, %f, %f\n", sq->normal[X], sq->normal[Y], sq->normal[Z]);
	printf("ref   : %f, %f, %f\n", ref_vec[X], ref_vec[Y], ref_vec[Z]);
	//printf("point : %f, %f, %f\n", point_vec[X], point_vec[Y], point_vec[Z]);
	printf("------\n");*/
	if (dot == 0)
	{
		if (calc_vector_mag(point_vec) <= sq->data.doubl)
			return (1);
		return (0);
	}
	if (dot < 0)
		dot *= -1;
	if (sqrt(dot) <= sq->data.doubl)
		return (1);
	return (0);
}

int	sq_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
				t_obj_struct *sq)
{
	double	ray_normal_dot;
	double	mag;
	double	plane_to_cam_vec[3];
	double	obj_surface_xyz[3];

	calc_3d_vector(ray_orig_xyz, sq->xyz, plane_to_cam_vec);
	ray_normal_dot = calc_dot_prod(ray_vec, sq->normal);
	*t_min = INFINITY;
	if (!ray_normal_dot)
		return (0);
	*t_min = calc_dot_prod(plane_to_cam_vec, sq->normal) / ray_normal_dot;
	/*here could check if t_min is larger than distance to viewport to
	  reduce checking rays unecessarily*/
	obj_surface_xyz[X] = ray_orig_xyz[X] + (*t_min * ray_vec[X]);
	obj_surface_xyz[Y] = ray_orig_xyz[Y] + (*t_min * ray_vec[Y]);
	obj_surface_xyz[Z] = ray_orig_xyz[Z] + (*t_min * ray_vec[Z]);
	if (sq_solve(t_min, obj_surface_xyz, sq))
		return (1);
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
