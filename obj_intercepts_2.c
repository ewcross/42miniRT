/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intercepts_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 16:43:09 by ecross            #+#    #+#             */
/*   Updated: 2020/05/12 16:49:10 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	calc_uv(double *u_v, double *v1, double *v2, double *v3)
{
	u_v[0] = (dot(v2, v2) * dot(v3, v1) - dot(v2, v1) * dot(v3, v2));
	u_v[0] /= (dot(v1, v1) * dot(v2, v2) - dot(v1, v2) * dot(v2, v1));
	u_v[1] = (dot(v1, v1) * dot(v3, v2) - dot(v1, v2) * dot(v3, v1));
	u_v[1] /= (dot(v1, v1) * dot(v2, v2) - dot(v1, v2) * dot(v2, v1));
}

int		tr_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
				t_obj_struct *tr)
{
	double	v1[3];
	double	v2[3];
	double	v3[3];
	double	u_v[2];
	double	obj_surface_xyz[3];

	if (!plane_intercept(t_min, ray_vec, ray_orig_xyz, tr))
		return (0);
	if (*t_min < 0)
	{
		*t_min = INFINITY;
		return (0);
	}
	get_point(obj_surface_xyz, ray_orig_xyz, ray_vec, *t_min);
	calc_3d_vector(tr->data.tr_points[0], tr->data.tr_points[2], v1);
	calc_3d_vector(tr->data.tr_points[0], tr->data.tr_points[1], v2);
	calc_3d_vector(tr->data.tr_points[0], obj_surface_xyz, v3);
	calc_uv(u_v, v1, v2, v3);
	if (u_v[0] < 0 || u_v[1] < 0 || u_v[0] > 1 || u_v[1] > 1 ||
		u_v[0] + u_v[1] > 1)
	{
		*t_min = INFINITY;
		return (0);
	}
	return (1);
}

void	get_cy_end_point(double *end, t_obj_struct *cy)
{
	end[X] = cy->xyz[X] + ((cy->data.cy_d_h[1] / 2) * cy->normal[X]);
	end[Y] = cy->xyz[Y] + ((cy->data.cy_d_h[1] / 2) * cy->normal[Y]);
	end[Z] = cy->xyz[Z] + ((cy->data.cy_d_h[1] / 2) * cy->normal[Z]);
}

double	get_p_height(double t_min, double *end, double *normal, double *ray_vec)
{
	double	ray_vec_len[3];
	double	point_to_base[3];

	ray_vec_len[X] = t_min * ray_vec[X];
	ray_vec_len[Y] = t_min * ray_vec[Y];
	ray_vec_len[Z] = t_min * ray_vec[Z];
	calc_3d_vector(ray_vec_len, end, point_to_base);
	return (dot(normal, point_to_base));
}
