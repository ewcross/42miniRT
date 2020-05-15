/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:31:30 by ecross            #+#    #+#             */
/*   Updated: 2020/05/15 14:34:55 by ecross           ###   ########.fr       */
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
# include "structs.h"

/*
**Error codes:
** (-1) Invalid object identifier.
** (-2) Wrong number of arguments in line.
** (-3) One or more invalid coordinate values.
** (-4) Invalid normal.
** (-5) Invalid object dimension value.
** (-6) One or more invalid colour values.
** (-7) Error creating list element.
** (-8) Only one 'R' and 'A' field allowed in input file.
*/

# define CHARSET "RAclspt"
# define MAX_RES_X 1440
# define MAX_RES_Y 900
# define R 0
# define G 1
# define B 2
# define X 0
# define Y 1
# define Z 2
# define BMP_HEADER_SIZE 14
# define BMP_INFO_SIZE 40
# define THICKNESS 0.0000000000001

# define ERR_BUFF_SIZE 75
# define BAD_IDENTIFIER "Invalid object identifier."
# define WRONG_ARG_NO "Wrong number of arguments in line."
# define POS_ERROR "One or more invalid coordinate values."
# define NORMAL_ERROR "Invalid normal."
# define DIMENSION_ERROR "Invalid object dimension value."
# define COLOUR_ERROR "One or more invalid colour values."
# define LINKED_LIST_ERROR "Error creating list element."
# define MULTIPLE_R_A "Only one 'R' and 'A' field allowed in input file."

void			sp_normal(double *surface_xyz, t_obj_struct *obj, double *norm);
void		    p_normal(double *surface_xyz, t_obj_struct *obj, double *norm);
void			sq_normal(double *surface_xyz, t_obj_struct *obj, double *norm);
void			cy_normal(double *surface_xyz, t_obj_struct *obj, double *norm);
void			ci_normal(double *surface_xyz, t_obj_struct *obj, double *norm);
void			tr_normal(double *surface_xyz, t_obj_struct *obj, double *norm);

int				solve_quadratic(double *t_min, double *ray_vec, double *ray_orig_xyz,
								t_obj_struct *sp);
int				plane_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
								t_obj_struct *pl);
int				sq_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
						t_obj_struct *pl);
int				tr_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
						t_obj_struct *pl);
int				cy_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
						t_obj_struct *pl);
int				ci_intercept(double *t_min, double *ray_vec, double *ray_orig_xyz,
						t_obj_struct *ci);
int				check_inside(t_obj_struct *obj, double *t_min, double* end_t,
								double *ray_vec);
void			calc_uv(double *u_v, double *v1, double *v2, double *v3);
void			get_cy_end_point(double *end, t_obj_struct *cy);
double			get_p_height(double t_min, double *end, double *normal,
								double *ray_vec);
void			sort_values(double t_min, double t_other, double *small, double *big);
int				check_ends(t_obj_struct *cy, double *t_min, double *end_t,
							double *ray_vec);
double			get_cy_disc(t_obj_struct *cy, double *ray_norm, double *end);

void			fill_corners(double c[][3], t_obj_struct *sq, double *d1, double *d2);
void			get_perp_vec(double *norm, double *perp_vec);
void			get_corners(t_obj_struct *sq, double corners[][3]);

void			calc_3d_vector(double *start, double *end, double *res);
void			calc_unit_vec(double *vec, double *unit_vec);
void			calc_unit_ints_vec(int *vec, int *unit_vec);
double			dot(double *vec1, double *vec2);
void			cross(double *vec1, double *vec2, double *res);
void			scale_ints_vector(int *vec, double factor, int *res);
void			scale_vector(double *vec, double factor, double *res);
double			calc_vector_mag(double *vec);
double			calc_ints_vector_mag(int *vec);
void			get_point(double *point, double *orig, double *vec, double dist);

void			*get_img_data(void *img_ptr, t_cam_struct *cam);
int				str_match(char *str, char *real);
int				check_args(int argc, char **argv);
void			create_image_list(t_win_struct *ws, t_scene_struct *s);
int				main(int argc, char **argv);
void			get_ray_vec(double *ray_vec, double *v_w_h, int *xy,
							t_scene_struct *s);
void			get_pixel_colour(t_scene_struct *s, t_ray_struct *ray);
int				trace_rays(t_scene_struct *s, void *img_addr, double *vp_w_h);
int				draw_image(t_scene_struct *s, void *img_addr);
void			add_img_to_list(t_win_struct *ws, void *img_ptr,
								char *img_addr, t_cam_struct *cam);
void			adj_cl(int *res_colour, t_obj_struct *obj, int *l_colour,
						double intensity);
void			rotate_about_x(double *ray, double *axis, int rev);
void			rotate_about_y(double *ray, double *axis, int rev);
void			rotate_about_z(double *ray, double angle);
void			rotate_ray(double *ray, t_cam_struct *cam);
void			get_correct_normal(double *cam_xyz, double *obj_xyz,
									double *obj_norm);
double			calc_light_intensity(t_scene_struct *s, t_obj_struct *obj,
										double *ray_vec, double t_min);
t_obj_struct	*get_next_elem(t_obj_struct *start, char id);
t_obj_struct	*find_closest_obj(double *t_min, t_scene_struct *s,
									double *ray_vec);
void			scale_light(t_scene_struct *s);
int				shadow_ray(double *surface_xyz, double *light_vec, t_obj_struct *obj,
							t_obj_struct *obj_list);

void			int_to_binary(char buff[4][8], int num);
int				binary_to_int(char binary[8]);
int				fill_little_endian(unsigned char *bmp, int num, int i);
int				fill_info_header(t_win_struct *ws, unsigned char *bmp, int i, int bpp);
int				fill_file_header(unsigned char *bmp, int fs);
void			fill_pixel_data(char *img_addr, unsigned char *bmp, int i, int fs);
int				create_bmp_file(unsigned char *bmp, int id, int fs);
int				create_bmp(t_win_struct *ws, t_img_struct *img, int id);
void			bmp(t_win_struct *ws, t_img_struct *img);

int				put_image(void *window_struct);
int				set_keys(int keycode, void *window_struct);
int				close_program(void *window_struct);
int				initialise_window(t_win_struct *ws);
void			colour_img_pixel(char *img_addr, int *xy, t_cam_struct *cam, int *colour);
void			shift_prev_cam(t_win_struct *ws);
void			shift_next_cam(t_win_struct *ws);

void			free_strs(char **strs);
void			free_img_list(t_img_struct *img);
void			free_light_list(t_l_struct *light);
void			free_cam_list(t_cam_struct *cam);
void			free_obj_list(t_obj_struct *obj);
void			free_scene_struct(t_scene_struct *s);

int				pos_in_set(char ch, char *set);
void			init_parse_func_arr(int (*func_arr[])(char *, t_scene_struct *));
int				parse_line(char *line, t_scene_struct *s);
void			init_win_struct(t_win_struct *ws, int res_x, int res_y);
void			init_scene_struct(t_scene_struct *s, double vp_dist);
int				parser(t_scene_struct *s, char *file);
void			fill_doubles(double *src, double *dst, int len);
void			fill_ints(int *src, int *dst, int len);
t_obj_struct	*create_obj_elem(double *xyz, double *normal, int *colour);
t_cam_struct	*create_cam_elem(double *xyz, double *normal, double fov);
t_l_struct		*create_l_elem(double *xyz, double brightness, int *colour);
void			add_obj_elem(t_scene_struct *s, t_obj_struct *elem);
void			add_cam_elem(t_scene_struct *s, t_cam_struct *elem);
void			add_l_elem(t_scene_struct *s, t_l_struct *elem);
int				simple_atoi(char *str);
double			tenths(char *str);
int				ft_atof(char *str, double *fl);
int				get_colour(char *str, int *colour);
int				get_data(char *str, double *data);
int				get_xyz(char *str, double *xyz);
int				len_str_arr(char **str_arr);
int				create_add_cam(t_scene_struct *s, double *xyz, double *normal, double fov);
int				create_add_l(t_scene_struct *s, double *xyz, double bright, int *colour);
int				create_add_obj(t_scene_struct *s, double *xyz, double *normal, int *colour);
int				check_normal(double *normal);
void			add_p_data(t_scene_struct *s);
void			calc_tr_normal(t_obj_struct *tr);
void			add_tr_data(t_scene_struct *s, double points[3][3]);
void			get_rotation_data(t_cam_struct *cam);
void			add_cam_data(t_scene_struct *s);
void			add_cy_data(t_scene_struct *s, double *diameter_height);
void			add_sp_data(t_scene_struct *s, double diameter);
void			add_sq_data(t_scene_struct *s, double side_size);
int				r_func(char *line, t_scene_struct *s);
int				a_func(char *line, t_scene_struct *s);
int				c_func(char *line, t_scene_struct *s);
int				l_func(char *line, t_scene_struct *s);
int				s_func(char *line, t_scene_struct *s);
int				p_func(char *line, t_scene_struct *s);
int				t_func(char *line, t_scene_struct *s);
int				cam_func(char *line, t_scene_struct *s);
int				cy_func(char *line, t_scene_struct *s);
int				sp_func(char *line, t_scene_struct *s);
int				sq_func(char *line, t_scene_struct *s);
#endif
