/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:13:25 by ecross            #+#    #+#             */
/*   Updated: 2020/05/15 11:41:25 by ecross           ###   ########.fr       */
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
	/*

int	*get_max_res(int *max_res_xy)
{
	void	*mlx_ptr;

	mlx_ptr = mlx_init()
	res = mlx_get_screen_size(mlx_ptr, max_res_xy, max_res_xy + 1);
	try
	free(mlx_ptr)
	or
	mlx_destroy_window(mlx_ptr);
}
	int		max_res_xy[2];
	max_res_xy = get_max_res(max_res_xy);

	 */
	/*if (s->res_xy[X] > max_res_xy[X])*/
	if (s->res_xy[X] > MAX_RES_X)
	{
		/*s->res_xy[X] = max_res_xy[X]*/
		s->res_xy[X] = MAX_RES_X;
	}
	/*if (s->res_xy[Y] > max_res_xy[Y])*/
	if (s->res_xy[Y] > MAX_RES_Y)
	{
		/*s->res_xy[Y] = max_res_xy[Y]*/
		s->res_xy[Y] = MAX_RES_Y;
	}
	free_strs(strs);
	return (0);
}

int	a_func(char *line, t_scene_struct *s)
{
	int		err_code;
	char	**strs;
	int		colour[3];

	if (s->ambient_ratio != -1)
		return (-8);
	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 3)
		return (-2);
	if (((err_code = get_data(strs[1], &(s->ambient_ratio))) < 0 &&
			s->ambient_ratio < 0) ||
		(err_code = get_colour(strs[2], colour)) < 0)
		return (err_code);
	fill_ints(colour, s->ambient_colour, 3);
	free_strs(strs);
	return (0);
}

int	c_func(char *line, t_scene_struct *s)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i + 1] == ' ')
		return (cam_func(line, s));
	else if (line[i + 1] == 'y')
		return (cy_func(line, s));
	else
		return (-1);
}

int	l_func(char *line, t_scene_struct *s)
{
	int				err_code;
	char			**strs;
	double			xyz[3];
	double			brightness;
	int				colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-2);
	if ((err_code = get_xyz(strs[1], xyz)) < 0 ||
		(err_code = get_data(strs[2], &brightness)) < 0 ||
		(err_code = get_colour(strs[3], colour)) < 0)
		return (err_code);
	if (!create_add_l(s, xyz, brightness, colour))
		return (-7);
	free_strs(strs);
	return (0);
}

int	s_func(char *line, t_scene_struct *s)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i + 1] == 'p')
		return (sp_func(line, s));
	else if (line[i + 1] == 'q')
		return (sq_func(line, s));
	else
		return (-1);
}
