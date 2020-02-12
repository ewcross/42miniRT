/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:31:30 by ecross            #+#    #+#             */
/*   Updated: 2020/02/12 15:15:13 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "libgnl.h"
# include "x11.h"

# define CHARSET "RAclspt"
# define R 0
# define G 1
# define B 2
# define X 0
# define Y 1
# define Z 2

typedef struct			s_win_struct
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	int					res_x;
	int					res_y;
}						t_win_struct;

typedef struct			s_cam_struct
{
	double				xyz[3];
	double				normal[3];
	double				fov;
	struct s_cam_struct	*next;
}						t_cam_struct;

typedef struct			s_l_struct
{
	double				xyz[3];
	double				brightness;
	int					colour[3];
	struct s_l_struct	*next;
}						t_l_struct;

typedef union			u_obj_data_union
{
	double				doubl;
	double				cy_diam_height[2];
	double				tr_points[3][3];
}						t_obj_data_union;

typedef struct			s_obj_struct
{
	char				id;
	double				xyz[3];
	double				normal[3];
	int					colour[3];
	t_obj_data_union	data;	
	struct s_obj_struct *next;
}						t_obj_struct;

typedef struct			s_scene_struct
{
	int					res_xy[2];
	double				viewport_distance;
	double				ambient_ratio;
	int					ambient_colour[3];
	t_obj_struct		*obj_list;
	t_cam_struct		*cam_list;
	t_l_struct			*l_list;
}						t_scene_struct;

int						set_keys(int keycode, void *t_win_struct);
void					dummy_parser(t_scene_struct *s);
int						pos_in_set(char ch, char *set);
void					init_func_arr(int (*func_arr[])(char *, t_scene_struct *));
int						parse_line(char *line, t_scene_struct *s);
int						len_str_arr(char **str_arr);
int						simple_atoi(char *str);
void					print_elem(t_obj_struct *elem);
int						parser(t_scene_struct *s, char *file);
int						r_func(char *line, t_scene_struct *s);
int						a_func(char *line, t_scene_struct *s);
int						c_func(char *line, t_scene_struct *s);
int						l_func(char *line, t_scene_struct *s);
int						s_func(char *line, t_scene_struct *s);
int						p_func(char *line, t_scene_struct *s);
int						t_func(char *line, t_scene_struct *s);
int						cam_func(char *line, t_scene_struct *s);
int						cy_func(char *line, t_scene_struct *s);
int						sp_func(char *line, t_scene_struct *s);
int						sq_func(char *line, t_scene_struct *s);

#endif
