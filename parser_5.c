/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:13:38 by ecross            #+#    #+#             */
/*   Updated: 2020/05/12 17:54:58 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		t_func(char *line, t_scene_struct *s)
{
	int				err_code;
	char			**strs;
	double			points[3][3];
	int				colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 5 || strs[0][1] != 'r')
		return (-2);
	if ((err_code = get_xyz(strs[1], points[0])) < 0 ||
		(err_code = get_xyz(strs[2], points[1])) < 0 ||
		(err_code = get_xyz(strs[3], points[2])) < 0 ||
		(err_code = get_colour(strs[4], colour)) < 0)
		return (err_code);
	if (!create_add_obj(s, NULL, NULL, colour))
		return (-7);
	add_tr_data(s, points);
	free_strs(strs);
	return (0);
}

void	get_rotation_data(t_cam_struct *cam)
{
	double			dot_prod;
	static double	z_axis[] = {0, 0, 1};

	dot_prod = dot(cam->normal, z_axis);
	cam->rot_angle = acos(dot_prod);
	if (dot_prod == 1)
		return ;
	if (dot_prod == -1)
	{
		cam->rot_axis[X] = 0;
		cam->rot_axis[Y] = 1;
		cam->rot_axis[Z] = 0;
		return ;
	}
	cross(cam->normal, z_axis, cam->rot_axis);
	calc_unit_vec(cam->rot_axis, cam->rot_axis);
	scale_vector(cam->rot_axis, -1, cam->rot_axis);
}

void	add_cam_data(t_scene_struct *s)
{
	t_cam_struct *cam;

	cam = s->cam_list;
	while (cam->next)
		cam = cam->next;
	get_rotation_data(cam);
}

int		cam_func(char *line, t_scene_struct *s)
{
	int				err_code;
	char			**strs;
	double			xyz[3];
	double			normal[3];
	double			fov;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-2);
	if ((err_code = get_xyz(strs[1], xyz)) < 0 ||
		(err_code = get_xyz(strs[2], normal)) < 0 ||
		(err_code = check_normal(normal)) < 0 ||
		(err_code = get_data(strs[3], &fov)) < 0)
		return (err_code);
	if (!create_add_cam(s, xyz, normal, fov))
		return (-7);
	add_cam_data(s);
	free_strs(strs);
	return (0);
}

void	add_cy_data(t_scene_struct *s, double *diameter_height)
{
	t_obj_struct *obj;

	obj = s->obj_list;
	while (obj->next)
		obj = obj->next;
	obj->id = 'c';
	fill_doubles(diameter_height, obj->data.cy_d_h, 2);
	obj->get_norm = cy_normal;
	obj->solve = cy_intercept;
}
