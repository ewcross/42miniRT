/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:31:30 by ecross            #+#    #+#             */
/*   Updated: 2020/02/11 10:49:09 by ecross           ###   ########.fr       */
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

typedef struct	s_win_struct
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			res_x;
	int			res_y;
}				t_win_struct;

typedef struct	s_scene_struct
{
	int			res_xy[2];
	double		viewport_distance;

	double		ambient_ratio;
	int			ambient_colour[3];

	double		cam_xyz[3];
	double		cam_normal[3];
	double		cam_fov;

	double		light_xyz[3];
	double		light_brightness;
	int			light_colour[3];

	double		sphere_xyz[3];
	double		sphere_diameter;
	int			sphere_colour[3];

	double		plane_xyz[3];
	double		plane_normal[3];
	int			plane_colour[3];

	double		square_xyz[3];
	double		square_normal[3];
	double		square_side_size;
	int			square_colour[3];

	double		cylinder_xyz[3];
	double		cylinder_normal[3];
	double		cylinder_diameter;
	double		cylinder_height;
	int			cylnder_colour[3];

	double		coords_of_points[3][3];
	int			triangle_colour[3];
}				t_scene_struct;

typedef struct			s_cam_struct
{
	double				cam_xyz[3];
	double				cam_normal[3];
	double				cam_fov;
	struct s_cam_struct *next;
}						t_cam_struct;

typedef struct				s_light_struct
{
	double					light_xyz[3];
	double					light_brightness;
	int						light_colour[3];
	struct s_light_struct	*next;
}							t_light_struct;

typedef struct				s_sphere_struct
{
	double					sphere_xyz[3];
	double					sphere_diameter;
	int						sphere_colour[3];
	struct s_sphere_struct	*next;
}							t_sphere_struct;

typedef						s_plane_struct
{
	double					plane_xyz[3];
	double					plane_normal[3];
	int						plane_colour[3];
	struct s_plane_struct	*next;
}							t_plane_struct;

typedef						s_square_struct
{
	double					square_xyz[3];
	double					square_normal[3];
	double					square_side_size;
	int						square_colour[3];
	struct s_plane_struct	*next;
}							t_square_struct;

typedef							s_cylinder_struct
{
	double						cylinder_xyz[3];
	double						cylinder_normal[3];
	double						cylinder_diameter;
	double						cylinder_height;
	int							cylnder_colour[3];
	struct s_cylinder_struct	*next;
}								t_cylinder_struct;

typedef							s_triangle_struct
{
	double						coords_of_points[3][3];
	int							triangle_colour[3];
	struct s_triangle_struct	*next;
}								t_triangle_struct;

int		set_keys(int keycode, void *t_win_struct);
int		draw_circle(void *t_win_struct);
void	put_circle(t_win_struct *ws, int x, int y, int colour);

void	dummy_parser(t_scene_struct *s);

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