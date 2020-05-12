/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:13:46 by ecross            #+#    #+#             */
/*   Updated: 2020/05/12 17:55:38 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		cy_func(char *line, t_scene_struct *s)
{
	int				err_code;
	char			**strs;
	double			xyz_norm[6];
	double			diameter_height[2];
	int				colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 6)
		return (-2);
	if ((err_code = get_xyz(strs[1], xyz_norm)) < 0 ||
		(err_code = get_xyz(strs[2], xyz_norm + 3)) < 0 ||
		(err_code = check_normal(xyz_norm + 3)) < 0 ||
		(err_code = get_colour(strs[3], colour)) < 0 ||
		(err_code = get_data(strs[4], diameter_height)) < 0 ||
		(err_code = get_data(strs[5], diameter_height + 1)) < 0)
		return (err_code);
	if (!create_add_obj(s, xyz_norm, xyz_norm + 3, colour))
		return (-7);
	add_cy_data(s, diameter_height);
	free_strs(strs);
	return (0);
}

void	add_sp_data(t_scene_struct *s, double diameter)
{
	t_obj_struct *obj;

	obj = s->obj_list;
	while (obj->next)
		obj = obj->next;
	obj->id = 's';
	obj->data.doubl = diameter;
	obj->get_norm = sp_normal;
	obj->solve = solve_quadratic;
}

int		sp_func(char *line, t_scene_struct *s)
{
	int				err_code;
	char			**strs;
	double			xyz[3];
	double			diameter;
	int				colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-2);
	if ((err_code = get_xyz(strs[1], xyz)) < 0 ||
		(err_code = get_data(strs[2], &diameter)) < 0 ||
		(err_code = get_colour(strs[3], colour)) < 0)
		return (err_code);
	if (!create_add_obj(s, xyz, NULL, colour))
		return (-7);
	add_sp_data(s, diameter);
	free_strs(strs);
	return (0);
}

void	add_sq_data(t_scene_struct *s, double side_size)
{
	t_obj_struct *obj;

	obj = s->obj_list;
	while (obj->next)
		obj = obj->next;
	obj->id = 'q';
	obj->data.doubl = side_size;
	obj->get_norm = sq_normal;
	obj->solve = sq_intercept;
}

int		sq_func(char *line, t_scene_struct *s)
{
	int				err_code;
	int				colour[3];
	char			**strs;
	double			xyz_norm[6];
	double			side_size;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 5)
		return (-2);
	if ((err_code = get_xyz(strs[1], xyz_norm)) < 0 ||
		(err_code = get_xyz(strs[2], xyz_norm + 3)) < 0 ||
		(err_code = check_normal(xyz_norm + 3)) < 0 ||
		(err_code = get_data(strs[3], &side_size)) < 0 ||
		(err_code = get_colour(strs[4], colour)) < 0)
		return (err_code);
	if (!create_add_obj(s, xyz_norm, xyz_norm + 3, colour))
		return (-7);
	add_sq_data(s, side_size);
	free_strs(strs);
	return (0);
}
