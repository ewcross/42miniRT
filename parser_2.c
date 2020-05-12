/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:08:48 by ecross            #+#    #+#             */
/*   Updated: 2020/05/12 17:52:26 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_win_struct(t_win_struct *ws, int res_x, int res_y)
{
	ws->mlx_ptr = NULL;
	ws->win_ptr = NULL;
	ws->img_list = NULL;
	ws->first_img_addr = NULL;
	ws->res_x = res_x;
	ws->res_y = res_y;
}

void	init_scene_struct(t_scene_struct *s, double vp_dist)
{
	s->vp_dist = vp_dist;
	s->res_xy[X] = 0;
	s->res_xy[Y] = 0;
	s->ambient_ratio = -1;
	s->obj_list = NULL;
	s->cam_list = NULL;
	s->l_list = NULL;
	s->cam_curr = NULL;
	s->l_curr = NULL;
}

int		pos_in_set(char ch, char *set)
{
	int i;

	if (ch == 0)
		return (-1);
	i = 0;
	while (set[i])
	{
		if (ch == set[i])
			return (i);
		i++;
	}
	return (-1);
}

int		get_xyz(char *str, double *xyz)
{
	int		i;
	char	**strs;

	strs = ft_split(str, ',');
	if (len_str_arr(strs) != 3)
		return (-3);
	i = 0;
	while (i < 3)
	{
		if (ft_atof(strs[i], xyz + i) == -1)
			return (-3);
		i++;
	}
	free_strs(strs);
	return (0);
}

int		len_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i])
		i++;
	return (i);
}
