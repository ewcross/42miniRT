/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_funcs_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 09:19:52 by ecross            #+#    #+#             */
/*   Updated: 2020/05/12 16:38:53 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double	dot(double *vec1, double *vec2)
{
	return ((vec1[0] * vec2[0]) + (vec1[1] * vec2[1]) + (vec1[2] * vec2[2]));
}

void	cross(double *vec1, double *vec2, double *res)
{
	res[X] = (vec1[Y] * vec2[Z]) - (vec1[Z] * vec2[Y]);
	res[Y] = (vec1[Z] * vec2[X]) - (vec1[X] * vec2[Z]);
	res[Z] = (vec1[X] * vec2[Y]) - (vec1[Y] * vec2[X]);
}

void	scale_ints_vector(int *vec, double factor, int *res)
{
	res[X] = vec[X] * factor;
	res[Y] = vec[Y] * factor;
	res[Z] = vec[Z] * factor;
}

void	scale_vector(double *vec, double factor, double *res)
{
	res[X] = vec[X] * factor;
	res[Y] = vec[Y] * factor;
	res[Z] = vec[Z] * factor;
}

void	calc_3d_vector(double *start, double *end, double *res)
{
	res[0] = end[0] - start[0];
	res[1] = end[1] - start[1];
	res[2] = end[2] - start[2];
}
