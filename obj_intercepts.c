/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intercepts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:48:54 by ecross            #+#    #+#             */
/*   Updated: 2020/02/21 14:45:33 by ecross           ###   ########.fr       */
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
	ray_normal_dot = dot(ray_vec, pl->normal);
	if (!ray_normal_dot)
	{
		*t_min = INFINITY;
		return (0);
	}
	*t_min = dot(plane_to_cam_vec, pl->normal) / ray_normal_dot;
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
	a = dot(ray_vec, ray_vec);
	b = 2 * dot(sphere_to_cam_vec, ray_vec);
	c = dot(sphere_to_cam_vec, sphere_to_cam_vec) - (r * r);
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
				t_obj_struct *sq)
{
	double	obj_surface_xyz[3];
	double	v[3];
	double	e1[3];
	double	e2[3];
	double	corners[4][3];

	if(!plane_intercept(t_min, ray_vec, ray_orig_xyz, sq))
		return (0);
	obj_surface_xyz[X] = ray_orig_xyz[X] + (*t_min * ray_vec[X]);
	obj_surface_xyz[Y] = ray_orig_xyz[Y] + (*t_min * ray_vec[Y]);
	obj_surface_xyz[Z] = ray_orig_xyz[Z] + (*t_min * ray_vec[Z]);
	get_corners(sq, corners);
	/*get vector between P (in plane) and one corner*/
	calc_3d_vector(corners[0], obj_surface_xyz, v);
	/*get vectors from this corner and adjacent corners - 2 edges*/
	calc_3d_vector(corners[0], corners[2], e1);
	calc_3d_vector(corners[0], corners[3], e2);
	/*printf("v (%.2f, %.2f, %.2f)\n", v[X], v[Y], v[Z]);
	printf("e1 (%.2f, %.2f, %.2f)\n", e1[X], e1[Y], e1[Z]);
	printf("e2 (%.2f, %.2f, %.2f)\n", e2[X], e2[Y], e2[Z]);*/
	if (dot(v, e1) < 0 || dot(v, e2) < 0)
		*t_min = INFINITY;
	else if (dot(v, e1) > calc_vector_mag(e1) || dot(v, e2) > calc_vector_mag(e2))
		*t_min = INFINITY;
	if (*t_min == INFINITY)
		return (0);
	printf("sq centre %f,%f,%f\n", sq->xyz[X], sq->xyz[Y], sq->xyz[Z]);
	printf("sq size %f\n", sq->data.doubl);
	return (1);
}

int	tr_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
				t_obj_struct *tr)
{
	double	v1[3];
	double	v2[3];
	double	v3[3];
	double	u_v[2];
	double	obj_surface_xyz[3];

	if(!plane_intercept(t_min, ray_vec, ray_orig_xyz, tr))
		return (0);
	/*if (*t_min < distance_to_viewport) to not check triangle points which are behind viewport
	{
		*t_min = INFINITY;
		return (0);
	}*/
	obj_surface_xyz[X] = ray_orig_xyz[X] + (*t_min * ray_vec[X]);
	obj_surface_xyz[Y] = ray_orig_xyz[Y] + (*t_min * ray_vec[Y]);
	obj_surface_xyz[Z] = ray_orig_xyz[Z] + (*t_min * ray_vec[Z]);
	calc_3d_vector(tr->data.tr_points[0], tr->data.tr_points[2], v1);
	calc_3d_vector(tr->data.tr_points[0], tr->data.tr_points[1], v2);
	calc_3d_vector(tr->data.tr_points[0], obj_surface_xyz, v3);
	u_v[0] = (dot(v2, v2) * dot(v3, v1) - dot(v2, v1) * dot(v3, v2));
	u_v[0] /= (dot(v1, v1) * dot(v2, v2) - dot(v1, v2) * dot(v2, v1));
	u_v[1] = (dot(v1, v1) * dot(v3, v2) - dot(v1, v2) * dot(v3, v1));
	u_v[1] /= (dot(v1, v1) * dot(v2, v2) - dot(v1, v2) * dot(v2, v1));
	if (u_v[0] < 0 || u_v[1] < 0 || u_v[0] > 1 || u_v[1] > 1 || u_v[0] + u_v[1] > 1)
	{
		*t_min = INFINITY;
		return (0);
	}
	return (1);
}

int	cy_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
				t_obj_struct *cy)
{
	*t_min = INFINITY;
	return (0);
}
