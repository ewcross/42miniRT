/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:31:30 by ecross            #+#    #+#             */
/*   Updated: 2020/02/03 18:56:39 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>

#define CHARSET "RAclspt"

typedef struct	s_struct
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
}				t_struct;

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "mlx.h"
#include "libft.h"

int		set_keys(int keycode, void *win_struct);
int		draw_circle(void *win_struct);
void	put_circle(t_struct *ws, int x, int y, int colour);

int		pos_in_set(char ch, char *set);
void	init_func_arr(int (*func_arr[])(char *));
int		parse_line(char *line);
int		len_str_arr(char **str_arr);
int		simple_atoi(char *str);

int	R_func(char *line);
int	A_func(char *line);
int	c_func(char *line);
int	l_func(char *line);
int	s_func(char *line);
int	p_func(char *line);
int	t_func(char *line);
int	cam_func(char *line);
int	cy_func(char *line);
int	sp_func(char *line);
int	sq_func(char *line);

#endif
