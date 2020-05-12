/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_scene_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 18:15:59 by ecross            #+#    #+#             */
/*   Updated: 2020/05/12 18:32:34 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void			get_correct_normal(double *cam_xyz, double *obj_xyz,
									double *obj_norm)
{
	double	mag1;
	double	mag2;
	double	dot_prod;
	double	cam_to_plane_vec[3];

	calc_3d_vector(cam_xyz, obj_xyz, cam_to_plane_vec);
	dot_prod = dot(cam_to_plane_vec, obj_norm);
	mag1 = calc_vector_mag(cam_to_plane_vec);
	mag2 = calc_vector_mag(obj_norm);
	if ((dot_prod / mag1 * mag2) > cos(M_PI / 2))
		scale_vector(obj_norm, -1, obj_norm);
}

double			calc_light_intensity(t_scene_struct *s, t_obj_struct *obj,
									double *ray_vec, double t_min)
{
	double	dot_prod;
	double	ray_unit_vec[3];
	double	obj_surface_xyz[3];
	double	to_light_vec[3];
	double	obj_norm_vec[3];

	get_point(obj_surface_xyz, s->cam_curr->xyz, ray_vec, t_min - THICKNESS);
	calc_3d_vector(obj_surface_xyz, s->l_curr->xyz, to_light_vec);
	if (shadow_ray(obj_surface_xyz, to_light_vec, obj, s->obj_list))
		return (0);
	obj->get_norm(obj_surface_xyz, obj, obj_norm_vec);
	if (obj->id != 's' && obj->id != 'c')
		get_correct_normal(s->cam_curr->xyz, obj->xyz, obj_norm_vec);
	else if (obj->inside)
		scale_vector(obj_norm_vec, -1, obj_norm_vec);
	if ((dot_prod = dot(to_light_vec, obj_norm_vec)) < 0)
		return (0);
	dot_prod /= (calc_vector_mag(to_light_vec) * calc_vector_mag(obj_norm_vec));
	return (dot_prod);
}

t_obj_struct	*get_next_elem(t_obj_struct *start, char id)
{
	if (!start)
		return (start);
	start = start->next;
	while (start)
	{
		if (start->id == id)
			return (start);
		start = start->next;
	}
	return (start);
}

t_obj_struct	*find_closest_obj(double *t_min, t_scene_struct *s,
									double *ray_vec)
{
	double			temp_t_min;
	t_obj_struct	*obj;
	t_obj_struct	*closest_obj;

	closest_obj = NULL;
	*t_min = INFINITY;
	obj = s->obj_list;
	while (obj)
	{
		obj->solve(&temp_t_min, ray_vec, s->cam_curr->xyz, obj);
		if (temp_t_min < *t_min && temp_t_min > s->vp_dist)
		{
			*t_min = temp_t_min;
			closest_obj = obj;
		}
		obj = obj->next;
	}
	return (closest_obj);
}
