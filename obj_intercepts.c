/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intercepts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:48:54 by ecross            #+#    #+#             */
/*   Updated: 2020/03/10 10:47:04 by ecross           ###   ########.fr       */
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
	double	a;
	double	b;
	double	c;
	double	r;
	double	a_b_c_r[4];
	double	discriminant;
	double	smallest_root;

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
	*t_min = ((-1 * b) - sqrt(discriminant)) / (2 * a);
	if (check_inside(sp, t_min, smallest_root))
		return (1);
	else if (smallest_root < *t_min)
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

int	check_ends(t_obj_struct *cy, double *t_min, double t_other, double *end, double *ray_vec)
{
	double	small;
	double	big;

	sort_values(*t_min, t_other, &small, &big);
	if (get_p_height(small, end, cy->normal, ray_vec) >= 0 &&
			get_p_height(small, end, cy->normal, ray_vec) <= cy->data.cy_d_h[1])
	{
		*t_min = small;
		return (1);
	}
	if (get_p_height(big, end, cy->normal, ray_vec) >= 0 &&
			get_p_height(big, end, cy->normal, ray_vec) <= cy->data.cy_d_h[1])
	{
		cy->inside = 1;
		*t_min = big;
		return (1);
	}
	return (0);
}

int	cy_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
				t_obj_struct *cy)
{
	double	discriminant;
	double	smallest;
	double	ray_norm[3];
	double	end_norm[3];
	double	end[3];

	*t_min = INFINITY;
	calc_unit_vec(cy->normal, cy->normal);
	get_cy_end_point(end, cy);
	get_point(end, end, ray_orig_xyz, -1);
	cross(ray_vec, cy->normal, ray_norm);
	if (calc_vector_mag(ray_norm) == 0)
		return (0);
	discriminant = dot(ray_norm, ray_norm) * pow(cy->data.cy_d_h[0] / 2, 2);
	discriminant -= pow(dot(end, ray_norm), 2);
	if (discriminant < 0)
		return (0);
	cross(end, cy->normal, end_norm);
	smallest = dot(ray_norm, end_norm) + sqrt(discriminant);
	smallest /= dot(ray_norm, ray_norm);
	*t_min = dot(ray_norm, end_norm) - sqrt(discriminant);
	*t_min /= dot(ray_norm, ray_norm);
	cy->inside = 0;
	if (check_inside(cy, t_min, smallest))
		return (1);
	if (check_ends(cy, t_min, smallest, end, ray_vec))
		return (1);
	*t_min = INFINITY;
	return (0);
}

int	ci_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
				t_obj_struct *ci)
{
	double	obj_surface_xyz[3];
	double	centre_to_point[3];

	if(!plane_intercept(t_min, ray_vec, ray_orig_xyz, ci))
		return (0);
	obj_surface_xyz[X] = ray_orig_xyz[X] + (*t_min * ray_vec[X]);
	obj_surface_xyz[Y] = ray_orig_xyz[Y] + (*t_min * ray_vec[Y]);
	obj_surface_xyz[Z] = ray_orig_xyz[Z] + (*t_min * ray_vec[Z]);
	calc_3d_vector(ci->xyz, obj_surface_xyz, centre_to_point);
	if (calc_vector_mag(centre_to_point) > ci->data.doubl / 2)
	{
		*t_min = INFINITY;
		return (0);
	}
	return (1);
}
