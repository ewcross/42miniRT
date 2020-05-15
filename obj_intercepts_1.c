/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intercepts_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 16:42:46 by ecross            #+#    #+#             */
/*   Updated: 2020/05/13 14:19:47 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	plane_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
					t_obj_struct *pl)
{
	double	ray_normal_dot;
	double	plane_to_cam_vec[3];

	ray_normal_dot = dot(ray_vec, pl->normal);
	if (!ray_normal_dot)
	{
		*t_min = INFINITY;
		return (0);
	}
	calc_3d_vector(ray_orig_xyz, pl->xyz, plane_to_cam_vec);
	*t_min = dot(plane_to_cam_vec, pl->normal) / ray_normal_dot;
	return (1);
}

int	check_inside(t_obj_struct *obj, double *t_min, double *end_t,
					double *ray_vec)
{
	int		ret;
	double	t_other;
	double	orig_t_min;

	ret = 0;
	orig_t_min = *t_min;
	t_other = end_t[3];
	if (obj->id == 'c')
		if (!(ret = check_ends(obj, t_min, end_t, ray_vec)))
			return (0);
	*t_min = orig_t_min;
	if (ret == 2)
		obj->inside = 0;
	if (t_other > 0 && *t_min < 0)
	{
		obj->inside = 1;
		*t_min = t_other;
		return (1);
	}
	else if (*t_min > 0 && t_other < 0)
	{
		obj->inside = 1;
		return (1);
	}
	return (0);
}

int	solve_quadratic(double *t_min, double *ray_vec, double *ray_orig_xyz,
					t_obj_struct *sp)
{
	double	sphere_to_cam_vec[3];
	double	abcr[4];
	double	discriminant;
	double	t_other[4];

	calc_3d_vector(sp->xyz, ray_orig_xyz, sphere_to_cam_vec);
	abcr[3] = sp->data.doubl / 2;
	abcr[0] = dot(ray_vec, ray_vec);
	abcr[1] = 2 * dot(sphere_to_cam_vec, ray_vec);
	abcr[2] = dot(sphere_to_cam_vec, sphere_to_cam_vec) - (abcr[3] * abcr[3]);
	discriminant = (abcr[1] * abcr[1]) - (4 * abcr[0] * abcr[2]);
	if (discriminant < 0)
	{
		*t_min = INFINITY;
		return (0);
	}
	t_other[3] = ((-1 * abcr[1]) + sqrt(discriminant)) / (2 * abcr[0]);
	*t_min = ((-1 * abcr[1]) - sqrt(discriminant)) / (2 * abcr[0]);
	if (check_inside(sp, t_min, t_other, ray_vec))
		return (1);
	else if (t_other[3] < *t_min)
		*t_min = t_other[3];
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

	if (!plane_intercept(t_min, ray_vec, ray_orig_xyz, sq))
		return (0);
	get_point(obj_surface_xyz, ray_orig_xyz, ray_vec, *t_min);
	get_corners(sq, corners);
	calc_3d_vector(corners[0], obj_surface_xyz, v);
	calc_3d_vector(corners[0], corners[2], e1);
	calc_3d_vector(corners[0], corners[3], e2);
	if (dot(v, e1) < 0 || dot(v, e2) < 0)
		*t_min = INFINITY;
	else if (dot(v, e1) > dot(e1, e1) || dot(v, e2) > dot(e2, e2))
		*t_min = INFINITY;
	if (*t_min == INFINITY)
		return (0);
	return (1);
}
