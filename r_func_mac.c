/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_func_mac.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 09:10:15 by ecross            #+#    #+#             */
/*   Updated: 2020/05/21 09:10:20 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	r_func(char *line, t_scene_struct *s)
{
	char	**strs;

	if (s->res_xy[X] && s->res_xy[Y])
		return (-8);
	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 3)
		return (-1);
	s->res_xy[X] = simple_atoi(strs[1]);
	s->res_xy[Y] = simple_atoi(strs[2]);
	if (s->res_xy[X] < 1 || s->res_xy[Y] < 1)
		return (-5);
	if (s->res_xy[X] > MAX_RES_X)
		s->res_xy[X] = MAX_RES_X;
	if (s->res_xy[Y] > MAX_RES_Y)
		s->res_xy[Y] = MAX_RES_Y;
	free_strs(strs);
	return (0);
}
