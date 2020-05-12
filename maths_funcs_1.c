/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_funcs_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 16:38:39 by ecross            #+#    #+#             */
/*   Updated: 2020/05/12 16:38:42 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double	calc_vector_mag(double *vec)
{
	return (sqrt((vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2])));
}

double	calc_ints_vector_mag(int *vec)
{
	return (sqrt((vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2])));
}

void	calc_unit_ints_vec(int *vec, int *unit_vec)
{
	double mag;

	mag = calc_ints_vector_mag(vec);
	printf("mag %f\n", mag);
	if (mag == 0)
		mag = 1;
	unit_vec[0] = vec[0] / mag;
	unit_vec[1] = vec[1] / mag;
	unit_vec[2] = vec[2] / mag;
}

void	calc_unit_vec(double *vec, double *unit_vec)
{
	double mag;

	mag = calc_vector_mag(vec);
	if (mag == 0)
		return ;
	unit_vec[0] = vec[0] / mag;
	unit_vec[1] = vec[1] / mag;
	unit_vec[2] = vec[2] / mag;
}

void	get_point(double *point, double *orig, double *vec, double dist)
{
	point[X] = orig[X] + (dist * vec[X]);
	point[Y] = orig[Y] + (dist * vec[Y]);
	point[Z] = orig[Z] + (dist * vec[Z]);
}
