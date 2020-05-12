/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:19:12 by ecross            #+#    #+#             */
/*   Updated: 2020/05/12 18:01:44 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_obj_struct	*create_obj_elem(double *xyz, double *normal, int *colour)
{
	t_obj_struct *elem;

	if (!(elem = (t_obj_struct*)malloc(sizeof(t_obj_struct))))
		return (NULL);
	elem->inside = 0;
	fill_doubles(xyz, elem->xyz, 3);
	fill_doubles(normal, elem->normal, 3);
	fill_ints(colour, elem->colour, 3);
	elem->next = NULL;
	return (elem);
}

t_cam_struct	*create_cam_elem(double *xyz, double *normal, double fov)
{
	t_cam_struct *elem;

	if (!(elem = (t_cam_struct*)malloc(sizeof(t_cam_struct))))
		return (NULL);
	fill_doubles(xyz, elem->xyz, 3);
	fill_doubles(normal, elem->normal, 3);
	elem->fov = fov;
	elem->next = NULL;
	return (elem);
}

t_l_struct		*create_l_elem(double *xyz, double brightness, int *colour)
{
	t_l_struct *elem;

	if (!(elem = (t_l_struct*)malloc(sizeof(t_l_struct))))
		return (NULL);
	fill_doubles(xyz, elem->xyz, 3);
	fill_ints(colour, elem->colour, 3);
	elem->brightness = brightness;
	elem->next = NULL;
	return (elem);
}

void			add_obj_elem(t_scene_struct *s, t_obj_struct *elem)
{
	t_obj_struct *temp;

	if (!s->obj_list)
	{
		s->obj_list = elem;
		return ;
	}
	temp = s->obj_list;
	while (temp->next)
		temp = temp->next;
	temp->next = elem;
}

void			add_cam_elem(t_scene_struct *s, t_cam_struct *elem)
{
	t_cam_struct *temp;

	temp = s->cam_list;
	if (!temp)
	{
		s->cam_list = elem;
		return ;
	}
	temp = s->cam_list;
	while (temp->next)
		temp = temp->next;
	temp->next = elem;
}
