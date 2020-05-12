/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:13:32 by ecross            #+#    #+#             */
/*   Updated: 2020/05/12 17:53:29 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		check_normal(double *normal)
{
	if (normal[X] == 0 && normal[Y] == 0 && normal[Z] == 0)
		return (-4);
	calc_unit_vec(normal, normal);
	return (0);
}

void	add_p_data(t_scene_struct *s)
{
	t_obj_struct *obj;

	obj = s->obj_list;
	while (obj->next)
		obj = obj->next;
	obj->id = 'p';
	obj->get_norm = p_normal;
	obj->solve = plane_intercept;
}

int		p_func(char *line, t_scene_struct *s)
{
	int				err_code;
	char			**strs;
	double			xyz[3];
	double			normal[3];
	int				colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4 || strs[0][1] != 'l')
		return (-2);
	if ((err_code = get_xyz(strs[1], xyz)) < 0 ||
		(err_code = get_xyz(strs[2], normal)) < 0 ||
		(err_code = check_normal(normal)) < 0 ||
		(err_code = get_colour(strs[3], colour)) < 0)
		return (err_code);
	if (!create_add_obj(s, xyz, normal, colour))
		return (-7);
	add_p_data(s);
	free_strs(strs);
	return (0);
}

void	calc_tr_normal(t_obj_struct *tr)
{
	double	vec1[3];
	double	vec2[3];
	double	cross_prod[3];

	calc_3d_vector(tr->data.tr_points[0], tr->data.tr_points[1], vec1);
	calc_3d_vector(tr->data.tr_points[0], tr->data.tr_points[2], vec2);
	cross(vec1, vec2, cross_prod);
	fill_doubles(cross_prod, tr->normal, 3);
	calc_unit_vec(tr->normal, tr->normal);
}

void	add_tr_data(t_scene_struct *s, double points[3][3])
{
	t_obj_struct *obj;

	obj = s->obj_list;
	while (obj->next)
		obj = obj->next;
	obj->id = 't';
	fill_doubles(points[0], obj->data.tr_points[0], 3);
	fill_doubles(points[1], obj->data.tr_points[1], 3);
	fill_doubles(points[2], obj->data.tr_points[2], 3);
	fill_doubles(points[0], obj->xyz, 3);
	calc_tr_normal(obj);
	obj->get_norm = tr_normal;
	obj->solve = tr_intercept;
}
