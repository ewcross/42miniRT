/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:13:25 by ecross            #+#    #+#             */
/*   Updated: 2020/05/21 09:09:52 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
