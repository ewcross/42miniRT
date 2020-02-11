/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:31:30 by ecross            #+#    #+#             */
/*   Updated: 2020/02/11 13:28:18 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
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
	double				cam_xyz[3];
	double				cam_normal[3];
	double				cam_fov;
	struct s_cam_struct *next;
}						t_cam_struct;

typedef struct			s_l_struct
{
	double				light_xyz[3];
	double				light_brightness;
	int					light_colour[3];
	struct s_l_struct	*next;
}						t_l_struct;

typedef struct			s_sp_struct
{
	double				sphere_xyz[3];
	double				sphere_diameter;
	int					sphere_colour[3];
	struct s_sp_struct	*next;
}						t_sp_struct;

typedef struct			s_pl_struct
{
	double				plane_xyz[3];
	double				plane_normal[3];
	int					plane_colour[3];
	struct s_pl_struct	*next;
}						t_pl_struct;

typedef struct			s_sq_struct
{
	double				square_xyz[3];
	double				square_normal[3];
	double				square_side_size;
	int					square_colour[3];
	struct s_sq_struct	*next;
}						t_sq_struct;

typedef struct			s_cy_struct
{
	double				cylinder_xyz[3];
	double				cylinder_normal[3];
	double				cylinder_diameter;
	double				cylinder_height;
	int					cylnder_colour[3];
	struct s_cy_struct	*next;
}						t_cy_struct;

typedef struct			s_tr_struct
{
	double				coords_of_points[3][3];
	int					triangle_colour[3];
	struct s_tr_struct	*next;
}						t_tr_struct;

typedef struct			s_scene_struct
{
	int					res_xy[2];
	double				viewport_distance;
	double				ambient_ratio;
	int					ambient_colour[3];
	t_cam_struct		*cam_list;
	t_l_struct			*l_list;
	t_sp_struct			*sp_list;
	t_pl_struct			*pl_list;
	t_sq_struct			*sq_list;
	t_cy_struct			*cy_list;
	t_tr_struct			*tr_list;
}						t_scene_struct;

int						set_keys(int keycode, void *t_win_struct);
void					dummy_parser(t_scene_struct *s);
int						pos_in_set(char ch, char *set);
void					init_func_arr(int (*func_arr[])(char *, t_scene_struct *));
int						parse_line(char *line, t_scene_struct *s);
int						len_str_arr(char **str_arr);
int						simple_atoi(char *str);
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
