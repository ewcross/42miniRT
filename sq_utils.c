/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sq_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:37:07 by ecross            #+#    #+#             */
/*   Updated: 2020/02/21 11:37:58 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "structs.h"

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

void	get_perp_vec(double *norm, double *perp_vec)
{
	int		i;
	double	dummy_vec[3];

	dummy_vec[X] = norm[X] + 0.1;
	dummy_vec[Y] = norm[Y];
	dummy_vec[Z] = norm[Z];
	cross(norm, dummy_vec, perp_vec);
	i = 1;
	while (perp_vec[X] == 0 && perp_vec[Y] == 0 && perp_vec[Z] == 0)
	{
		dummy_vec[i % 3] += 10 - i;
		cross(norm, dummy_vec, perp_vec);
		if (i == 10000)
		{
			printf("Error\nCannot find dummy vector in square generator\n");
			return ;
		}
		i++;
	}
}

void	get_corners(t_obj_struct *sq, double corners[][3])
{
	double	diagonal1[3];
	double	diagonal2[3];

	/*generate linearly independent vector*/
	/*handle zero normal case*/
	get_perp_vec(sq->normal, diagonal1);
	/*calculate cross of two vectors to give vector perpendicular to both
	  and so to the square normal and normalise this vector - this is one square diagonal*/
	calc_unit_vec(diagonal1, diagonal1);
	/*calculate cross of this diagonal with the normal to give a vector perpendicular
	  to both and normalise this - this is the second diagonal*/
	cross(sq->normal, diagonal1, diagonal2);
	calc_unit_vec(diagonal2, diagonal2);
	/*each pair of opposite square corners is found by moving side_size/2 along
	  each diagonal form the centre in opposite directions*/
	fill_corners(corners, sq, diagonal1, diagonal2);
}
