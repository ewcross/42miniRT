/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_scene_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 18:16:05 by ecross            #+#    #+#             */
/*   Updated: 2020/05/12 18:32:11 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	scale_light(t_scene_struct *s)
{
	double		light_total;
	double		scale;
	t_l_struct	*light;

	light_total = 0;
	light = s->l_list;
	while (light)
	{
		light_total += light->brightness;
		light = light->next;
	}
	scale = 1 / (s->ambient_ratio + light_total);
	s->ambient_ratio *= scale;
	light = s->l_list;
	while (light)
	{
		light->brightness *= scale;
		light = light->next;
	}
}

int		shadow_ray(double *surface_xyz, double *light_vec, t_obj_struct *obj,
				t_obj_struct *obj_list)
{
	double	t_min;
	double	light_unit_vec[3];

	calc_unit_vec(light_vec, light_unit_vec);
	t_min = INFINITY;
	while (obj_list)
	{
		if (obj_list == obj)
		{
			if (!((obj->id == 's' || obj->id == 'c') && obj->inside))
			{
				obj_list = obj_list->next;
				continue;
			}
		}
		if (obj_list->solve(&t_min, light_unit_vec, surface_xyz, obj_list) &&
				t_min > 0 && t_min < calc_vector_mag(light_vec))
			return (1);
		obj_list = obj_list->next;
	}
	return (0);
}
