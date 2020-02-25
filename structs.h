/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:14:28 by ecross            #+#    #+#             */
/*   Updated: 2020/02/25 16:33:46 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "header.h"

typedef struct			s_img_struct
{
	void				*img_ptr;
	struct s_img_struct	*next;
}						t_img_struct;

typedef struct			s_win_struct
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_img_struct		*img_list;
	t_img_struct		*first_img_addr;
	int					res_x;
	int					res_y;
}						t_win_struct;

typedef struct			s_cam_struct
{
	int					bpp;
	int					line_size;
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
	double				cy_d_h[2];
	double				tr_points[3][3];
}						t_obj_data_union;

typedef struct			s_obj_struct
{
	char				id;
	double				xyz[3];
	double				normal[3];
	int					colour[3];
	t_obj_data_union	data;	
	void				(*get_norm)(double *, struct s_obj_struct *, double *);
	int					(*solve)(double *, double *, double *, struct s_obj_struct *);
	struct s_obj_struct *next;
}						t_obj_struct;

typedef struct			s_ray_struct
{
	int					colour[3];
	double				t_min;
	double				ray_vec[3];
	t_obj_struct		*closest_obj;
}						t_ray_struct;

typedef struct			s_scene_struct
{
	int					res_xy[2];
	double				vp_dist;
	double				ambient_ratio;
	int					ambient_colour[3];
	t_obj_struct		*obj_list;
	t_cam_struct		*cam_list;
	t_l_struct			*l_list;
	t_cam_struct		*cam_curr;
	t_l_struct			*l_curr;
}						t_scene_struct;

#endif
