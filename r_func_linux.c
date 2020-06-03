/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_func_linux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 09:10:35 by ecross            #+#    #+#             */
/*   Updated: 2020/05/21 09:10:44 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	r_func(char *line, t_scene_struct *s)
{
	char	**strs;
	int		max_res_xy[2];
	void	*mlx_ptr;

	if (s->res_xy[X] && s->res_xy[Y])
		return (-8);
	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 3)
		return (-1);
	s->res_xy[X] = simple_atoi(strs[1]);
	s->res_xy[Y] = simple_atoi(strs[2]);
	if (s->res_xy[X] < 1 || s->res_xy[Y] < 1)
		return (-5);
	mlx_ptr = mlx_init();
	mlx_get_screen_size(mlx_ptr, max_res_xy, max_res_xy + 1);
	free(mlx_ptr);
	if (s->res_xy[X] > max_res_xy[X])
		s->res_xy[X] = max_res_xy[X];
	if (s->res_xy[Y] > max_res_xy[Y])
		s->res_xy[Y] = max_res_xy[Y];
	free_strs(strs);
	return (0);
}
