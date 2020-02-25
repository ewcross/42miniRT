/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:31:30 by ecross            #+#    #+#             */
/*   Updated: 2020/02/25 14:42:29 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "structs.h"
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
# define ERR_BUFF_SIZE 75
# define BAD_IDENTIFIER "Invalid object identifier."
# define WRONG_ARG_NO "Wrong number of arguments in line."
# define POS_ERROR "One or more invalide coordinate values."
# define NORMAL_ERROR "One or more invalid coordinate values."
# define DIMENSION_ERROR "Invalid object dimension value."
# define COLOUR_ERROR "One or more invalid colour values."
# define LINKED_LIST_ERROR "Error creating list element."
# define MULTIPLE_R_A "Only one 'R' and 'A' field allowed in input file"

void	sp_normal(double *surface_xyz, t_obj_struct *obj, double *norm);
void    p_normal(double *surface_xyz, t_obj_struct *obj, double *norm);
void	sq_normal(double *surface_xyz, t_obj_struct *obj, double *norm);
void	cy_normal(double *surface_xyz, t_obj_struct *obj, double *norm);
void	ci_normal(double *surface_xyz, t_obj_struct *obj, double *norm);
void	tr_normal(double *surface_xyz, t_obj_struct *obj, double *norm);

int		solve_quadratic(double *t_min, double *ray_vec, double *ray_orig_xyz,
						t_obj_struct *sp);
int		plane_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
						t_obj_struct *pl);
int		sq_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
				t_obj_struct *pl);
int		tr_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
				t_obj_struct *pl);
int		cy_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
				t_obj_struct *pl);
int		ci_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
				t_obj_struct *ci);

void	get_cy_end_point(double *end, t_obj_struct *cy);
double	get_p_height(double t_min, double *end, double *normal, double *ray_vec);

void	fill_corners(double c[][3], t_obj_struct *sq, double *d1, double *d2);
void	get_perp_vec(double *norm, double *perp_vec);
void	get_corners(t_obj_struct *sq, double corners[][3]);

void	calc_3d_vector(double *start, double *end, double *res);
void	calc_unit_vec(double *vec, double *unit_vec);
double	dot(double *vec1, double *vec2);
void	cross(double *vec1, double *vec2, double *res);
void	scale_vector(double *vec, double factor);
double	calc_vector_mag(double *vec);

void	fill_doubles(double *src, double *dst, int len);
void	fill_ints(int *src, int *dst, int len);

int		put_image(void *window_struct);
int		set_keys(int keycode, void *window_struct);
int		close_program(void *window_struct);
int		initialise_window(t_win_struct *ws);
void	colour_img_pixel(char *img_addr, int *xy, t_cam_struct *cam, int *colour);

void	free_scene_struct(t_scene_struct *s);
void	print_elem(t_obj_struct *elem);
void	add_img_to_list(t_win_struct *ws, void	*img_ptr);
void	free_img_list(t_img_struct *img);

int		pos_in_set(char ch, char *set);
void	init_parse_func_arr(int (*func_arr[])(char *, t_scene_struct *));
int		parse_line(char *line, t_scene_struct *s);
int		len_str_arr(char **str_arr);
int		simple_atoi(char *str);
void	init_win_struct(t_win_struct *ws);
int		parser(t_scene_struct *s, char *file);

int		r_func(char *line, t_scene_struct *s);
int		a_func(char *line, t_scene_struct *s);
int		c_func(char *line, t_scene_struct *s);
int		l_func(char *line, t_scene_struct *s);
int		s_func(char *line, t_scene_struct *s);
int		p_func(char *line, t_scene_struct *s);
int		t_func(char *line, t_scene_struct *s);
int		cam_func(char *line, t_scene_struct *s);
int		cy_func(char *line, t_scene_struct *s);
int		sp_func(char *line, t_scene_struct *s);
int		sq_func(char *line, t_scene_struct *s);

#endif
