/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intercepts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:48:54 by ecross            #+#    #+#             */
/*   Updated: 2020/03/10 11:44:55 by ecross           ###   ########.fr       */
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

int	check_inside(t_obj_struct *obj, double *t_min, double t_other)
{
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
	double	t_other;

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
	t_other = ((-1 * abcr[1]) + sqrt(discriminant)) / (2 * abcr[0]);
	*t_min = ((-1 * abcr[1]) - sqrt(discriminant)) / (2 * abcr[0]);
	if (check_inside(sp, t_min, t_other))
		return (1);
	else if (t_other < *t_min)
		*t_min = t_other;
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

void	calc_uv(double *u_v, double *v1, double *v2, double *v3)
{
	u_v[0] = (dot(v2, v2) * dot(v3, v1) - dot(v2, v1) * dot(v3, v2));
	u_v[0] /= (dot(v1, v1) * dot(v2, v2) - dot(v1, v2) * dot(v2, v1));
	u_v[1] = (dot(v1, v1) * dot(v3, v2) - dot(v1, v2) * dot(v3, v1));
	u_v[1] /= (dot(v1, v1) * dot(v2, v2) - dot(v1, v2) * dot(v2, v1));
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

void	sort_values(double t_min, double t_other, double *small, double *big)
{
	if (t_other < t_min)
	{
		*big = t_min;
		*small = t_other;
	}
	else
	{
		*big = t_other;
		*small = t_min;
	}
}

int	check_ends(t_obj_struct *cy, double *t_min, double *end_t, double *ray_vec)
{
	double	small;
	double	big;
	double	small_h;
	double	big_h;

	sort_values(*t_min, end_t[3], &small, &big);
	small_h = get_p_height(small, end_t, cy->normal, ray_vec);
	big_h = get_p_height(big, end_t, cy->normal, ray_vec);
	if (small_h >= 0 && small_h <= cy->data.cy_d_h[1])
	{
		*t_min = small;
		return (1);
	}
	if (big_h >= 0 && big_h <= cy->data.cy_d_h[1])
	{
		cy->inside = 1;
		*t_min = big;
		return (1);
	}
	return (0);
}

double	get_cy_disc(t_obj_struct *cy, double *ray_norm, double *end)
{
	double	d;

	d = dot(ray_norm, ray_norm) * pow(cy->data.cy_d_h[0] / 2, 2);
	d -= pow(dot(end, ray_norm), 2);
	return (d);
}

int	cy_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
				t_obj_struct *cy)
{
	double	d;
	double	t_other;
	double	ray_n[3];
	double	end_norm[3];
	double	end_t[4];

	*t_min = INFINITY;
	calc_unit_vec(cy->normal, cy->normal);
	get_cy_end_point(end_t, cy);
	get_point(end_t, end_t, ray_orig_xyz, -1);
	cross(ray_vec, cy->normal, ray_n);
	if (calc_vector_mag(ray_n) == 0 || (d = get_cy_disc(cy, ray_n, end_t)) < 0)
		return (0);
	cross(end_t, cy->normal, end_norm);
	end_t[3]= (dot(ray_n, end_norm) + sqrt(d)) / dot(ray_n, ray_n);
	*t_min = (dot(ray_n, end_norm) - sqrt(d)) / dot(ray_n, ray_n);
	cy->inside = 0;
	if (check_inside(cy, t_min, end_t[3]))
		return (1);
	if (check_ends(cy, t_min, end_t, ray_vec))
		return (1);
	*t_min = INFINITY;
	return (0);
}
