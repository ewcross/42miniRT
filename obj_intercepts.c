/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intercepts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:48:54 by ecross            #+#    #+#             */
/*   Updated: 2020/02/21 10:50:54 by ecross           ###   ########.fr       */
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

void	fill_corners(double c[][3], t_obj_struct *sq, double *d1, double *d2)
{
	int		i;
	int		j;
	double	len;

	len = sqrt(2 * pow(sq->data.doubl / 2, 2));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 3)
		{
			if (i < 2)
				c[i][j] = sq->xyz[j] + (pow(-1, i) * len * d1[j]);
			else
				c[i][j] = sq->xyz[j] + (pow(-1, i) * len * d2[j]);
			j++;
		}
		i++;
	}
}

void	get_corners(t_obj_struct *sq, double corners[][3])
{
	double	dummy_vec[3];
	double	diagonal1[3];
	double	diagonal2[3];

	/*generate linearly independent vector*/
	dummy_vec[X] = sq->normal[X] + 0.1;
	dummy_vec[Y] = sq->normal[Y];
	dummy_vec[Z] = sq->normal[Z];
	/*calculate cross of two vectors to give vector perpendicular to both
	  and so to the square normal and normalise this vector - this is one square diagonal*/
	printf("dummy (%.2f, %.2f, %.2f)\n", dummy_vec[X], dummy_vec[Y], dummy_vec[Z]);
	cross(sq->normal, dummy_vec, diagonal1);
	printf("d1 (%.2f, %.2f, %.2f)\n", diagonal1[X], diagonal1[Y], diagonal1[Z]);
	calc_unit_vec(diagonal1, diagonal1);
	printf("d1 (%.2f, %.2f, %.2f)\n", diagonal1[X], diagonal1[Y], diagonal1[Z]);
	/*calculate cross of this diagonal with the normal to give a vector perpendicular
	  to both and normalise this - this is the second diagonal*/
	cross(sq->normal, diagonal1, diagonal2);
	calc_unit_vec(diagonal2, diagonal2);
	printf("d1 (%.2f, %.2f, %.2f)\n", diagonal1[X], diagonal1[Y], diagonal1[Z]);
	printf("d2 (%.2f, %.2f, %.2f)\n", diagonal2[X], diagonal2[Y], diagonal2[Z]);
	/*each pair of opposite square corners is found by moving side_size/2 along
	  each diagonal form the centre in opposite directions*/
	fill_corners(corners, sq, diagonal1, diagonal2);
}

int		sq_solve(double *t_min, double *point, t_obj_struct *sq)
{
	double	corners[4][3];

	get_corners(sq, corners);
	/*
	printf("p1 (%.2f, %.2f, %.2f)\n", corners[0][X], corners[0][Y], corners[0][Z]);
	printf("p2 (%.2f, %.2f, %.2f)\n", corners[1][X], corners[1][Y], corners[1][Z]);
	printf("p3 (%.2f, %.2f, %.2f)\n", corners[2][X], corners[2][Y], corners[2][Z]);
	printf("p4 (%.2f, %.2f, %.2f)\n", corners[3][X], corners[3][Y], corners[3][Z]);
	*/
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
	ray_normal_dot = dot(ray_vec, sq->normal);
	*t_min = INFINITY;
	if (!ray_normal_dot)
		return (0);
	*t_min = dot(plane_to_cam_vec, sq->normal) / ray_normal_dot;
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
