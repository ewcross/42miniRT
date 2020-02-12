/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:14:09 by ecross            #+#    #+#             */
/*   Updated: 2020/02/12 19:16:07 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "structs.h"

void	init_win_struct(t_win_struct *ws)
{
	ws->mlx_ptr = NULL;
	ws->win_ptr = NULL;
	ws->img_ptr = NULL;
	ws->res_x = 0;
	ws->res_y = 0;
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

void	init_parse_func_arr(int (*func_arr[])(char *, t_scene_struct *))
{
	func_arr[0] = r_func;
	func_arr[1] = a_func;
	func_arr[2] = c_func;
	func_arr[3] = l_func;
	func_arr[4] = s_func;
	func_arr[5] = p_func;
	func_arr[6] = t_func;
}

int		parse_line(char *line, t_scene_struct *s)
{
	int		i;
	int		pos;
	int		(*func_arr[7])(char *, t_scene_struct *);

	init_parse_func_arr(func_arr);
	i = 0;
	while (line[i] == ' ')
		i++;
	if (!line[i])
		return (0);
	if ((pos = pos_in_set(line[i], CHARSET)) > -1)
		return(func_arr[pos](line, s));
	else
		return (-1);
}

int		parser(t_scene_struct *s, char *file)
{
	int				fd;
	char			*line;
	t_obj_struct	*elem;
	t_cam_struct	*cam;
	t_l_struct		*light;

	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (parse_line(line, s))
			printf("\n\n***ERROR***\ncheck line: \"%s\"\n", line);
	}
	printf("printing struct basics:\n\n");
	printf("res_x = %d, res_y %d\n\n", s->res_xy[X], s->res_xy[Y]);
	printf("ambient ratio  = %f\n", s->ambient_ratio);
	printf("ambient colour: %d,%d,%d\n\n", s->ambient_colour[R], s->ambient_colour[G], s->ambient_colour[B]);
	printf("printing obj list:\n");
	if (s->obj_list)
	{
		elem = s->obj_list;
		while (elem)
		{
			printf("\nelem:\n\n");
			print_elem(elem);
			elem = elem->next;
		}
	}
	/*printf("printing cam list:\n");
	if (s->cam_list)
	{
		cam = s->cam_list;
		while (cam)
		{
			printf("\ncamera\n\n");
			cam = cam->next;
		}
	}
	printf("printing light list:\n");
	if (s->l_list)
	{
		light = s->l_list;
		while (light)
		{
			printf("\nlight\n\n");
			light = light->next;
		}
	}*/
	return (0);
}
