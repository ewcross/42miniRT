/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:14:09 by ecross            #+#    #+#             */
/*   Updated: 2020/02/11 14:48:55 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

void	init_func_arr(int (*func_arr[])(char *, t_scene_struct *))
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

	init_func_arr(func_arr);
	i = 0;
	while (line[i] == ' ')
		i++;
	if ((pos = pos_in_set(line[i], CHARSET)) > -1)
		return(func_arr[pos](line, s));
	else
		return (-1);
}

/*replace with parser function - start of parsing process*/
int main(int argc, char **argv)
{
	char *line;
	t_scene_struct s;
	t_win_struct ws;
	t_obj_struct *elem;

	init_win_struct(&ws);
	s.obj_list = NULL;

	line = argv[1];
	if (parse_line(line, &s) == -2)
		printf("check line: \"%s\"\n", line);
	else if (parse_line(line, &s))
		printf("malloc error\n");
	printf("printing obj list:\n\n");
	if (s.obj_list)
	{
		elem = s.obj_list;
		while (elem)
		{
			printf("\nelem:\n\n");
			print_elem(elem);
			elem = elem->next;
		}
	}
	return (0);
}
