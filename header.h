/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:31:30 by ecross            #+#    #+#             */
/*   Updated: 2020/02/04 10:29:01 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "mlx.h"
#include "libft.h"

#define CHARSET "RAclspt"
#define R 0
#define G 1
#define B 2
#define X 0
#define Y 1
#define Z 2

typedef struct	s_struct
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
}				window_struct;

typedef struct	s_struct
{
	char		res;
	int			res_xy[2];

	char		ambient;
	float		ambient_ratio;
	int			ambient_colour[3];

	char		cam;
	float		cam_coords[3];
	float		cam_normal[3];
	float		cam_fov;

	char		light;
	float		light_coords[3];
	float		light_brightness;
	int			light_colour[3];

	char		sphere;
	float		sphere_coords[3];
	float		sphere_diamete;
	int			sphere_colour[3];

	char		plane;
	float		plane_coords[3];
	float		plane_normal[3];
	int			plane_colours[3];

	char		square;
	float		square_coords[3];
	float		square_normal[3];
	float		square_side_size;
	int			square_colour[3];

	char		cylinder;
	float		cylinder_coords[3];
	float		cylinder_normal[3];
	float		cylinder_diameter;
	float		cylinder_height;
	int			cylnder_colour[3];

	char		triangle;
	float		coords_of_points[3][3];
	int			triangle_colour[3];
}				scene_struct;

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
