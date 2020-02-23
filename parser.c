/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:14:09 by ecross            #+#    #+#             */
/*   Updated: 2020/02/23 14:28:31 by ecross           ###   ########.fr       */
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

void	fill_buff_str(char *src, char *dst, int len)
{
	int	i;

	i = 0;
	while (src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = src[i];
}

void	init_error_messages(char err_msgs[][ERR_BUFF_SIZE])
{
	fill_buff_str(BAD_IDENTIFIER, err_msgs[0], ERR_BUFF_SIZE);
	fill_buff_str(WRONG_ARG_NO, err_msgs[1] , ERR_BUFF_SIZE);
	fill_buff_str(POS_ERROR, err_msgs[2], ERR_BUFF_SIZE);
	fill_buff_str(NORMAL_ERROR, err_msgs[3], ERR_BUFF_SIZE);
	fill_buff_str(DIMENSION_ERROR, err_msgs[4], ERR_BUFF_SIZE);
	fill_buff_str(COLOUR_ERROR, err_msgs[5], ERR_BUFF_SIZE);
	fill_buff_str(LINKED_LIST_ERROR, err_msgs[6], ERR_BUFF_SIZE);
	fill_buff_str(MULTIPLE_R_A, err_msgs[7], ERR_BUFF_SIZE);
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
	int				err_code;
	char			*line;
	char			err_msgs[8][ERR_BUFF_SIZE];
	t_obj_struct	*elem;
	t_cam_struct	*cam;
	t_l_struct		*light;

	fd = open(file, O_RDONLY);
	init_error_messages(err_msgs);
	while (get_next_line(fd, &line))
	{
		if ((err_code = parse_line(line, s)))
		{
			ft_putstr_fd("Error\n", 1);
			ft_putstr_fd(err_msgs[(err_code * -1) - 1], 1);
			ft_putstr_fd("\nCheck line: ", 1);
			ft_putstr_fd(line, 1);
			ft_putstr_fd("\n", 1);
			return (0);
		}
	}
	return (1);
}
