/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_normals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:49:04 by ecross            #+#    #+#             */
/*   Updated: 2020/05/12 16:58:27 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "structs.h"

void	sp_normal(double *surface_xyz, t_obj_struct *obj, double *norm)
{
	calc_3d_vector(obj->xyz, surface_xyz, norm);
	calc_unit_vec(norm, norm);
}

void	p_normal(double *surface_xyz, t_obj_struct *obj, double *norm)
{
	fill_doubles(obj->normal, norm, 3);
	calc_unit_vec(norm, norm);
}

void	sq_normal(double *surface_xyz, t_obj_struct *obj, double *norm)
{
	fill_doubles(obj->normal, norm, 3);
	calc_unit_vec(norm, norm);
}

void	cy_normal(double *surface_xyz, t_obj_struct *obj, double *norm)
{
	double	height;
	double	end[3];
	double	p_to_base[3];
	double	height_xyz[3];

	get_cy_end_point(end, obj);
	calc_3d_vector(end, surface_xyz, p_to_base);
	height = dot(obj->normal, p_to_base);
	height_xyz[X] = height * obj->normal[X];
	height_xyz[Y] = height * obj->normal[Y];
	height_xyz[Z] = height * obj->normal[Z];
	calc_3d_vector(height_xyz, surface_xyz, norm);
	calc_3d_vector(end, norm, norm);
	calc_unit_vec(norm, norm);
}

void	tr_normal(double *surface_xyz, t_obj_struct *obj, double *norm)
{
	fill_doubles(obj->normal, norm, 3);
	calc_unit_vec(norm, norm);
}
