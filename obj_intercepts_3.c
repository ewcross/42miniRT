/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intercepts_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 16:43:23 by ecross            #+#    #+#             */
/*   Updated: 2020/05/13 13:56:37 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

int		check_ends(t_obj_struct *cy, double *t_min, double *end_t,
					double *ray_vec)
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
		return (2);
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

int		cy_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
				t_obj_struct *cy)
{
	double	d;
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
	end_t[3] = (dot(ray_n, end_norm) + sqrt(d)) / dot(ray_n, ray_n);
	*t_min = (dot(ray_n, end_norm) - sqrt(d)) / dot(ray_n, ray_n);
	cy->inside = 0;
	if (check_inside(cy, t_min, end_t, ray_vec))
		return (1);
	if (check_ends(cy, t_min, end_t, ray_vec))
		return (1);
	*t_min = INFINITY;
	return (0);
}
