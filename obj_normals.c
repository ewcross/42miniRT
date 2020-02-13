/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_normals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:49:04 by ecross            #+#    #+#             */
/*   Updated: 2020/02/13 12:04:52 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "structs.h"

void	sp_normal(double *surface_xyz, t_obj_struct *obj, double *norm)
{
	calc_3d_vector(obj->xyz, surface_xyz, norm);
	calc_unit_vec(norm, norm);
}

void    p_normal(double *surface_xyz, t_obj_struct *obj, double *norm)
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
	fill_doubles(obj->normal, norm, 3);
	calc_unit_vec(norm, norm);
}

void	tr_normal(double *surface_xyz, t_obj_struct *obj, double *norm)
{
	return ;
}
