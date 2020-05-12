/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:19:24 by ecross            #+#    #+#             */
/*   Updated: 2020/05/12 18:03:25 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	add_l_elem(t_scene_struct *s, t_l_struct *elem)
{
	t_l_struct *temp;

	if (!s->l_list)
	{
		s->l_list = elem;
		return ;
	}
	temp = s->l_list;
	while (temp->next)
		temp = temp->next;
	temp->next = elem;
}

int		create_add_cam(t_scene_struct *s, double *xyz, double *normal,
						double fov)
{
	t_cam_struct *elem;

	if (!(elem = create_cam_elem(xyz, normal, fov)))
		return (0);
	add_cam_elem(s, elem);
	return (1);
}

int		create_add_l(t_scene_struct *s, double *xyz, double bright, int *colour)
{
	t_l_struct	*elem;

	if (!(elem = create_l_elem(xyz, bright, colour)))
		return (0);
	add_l_elem(s, elem);
	return (1);
}

int		create_add_obj(t_scene_struct *s, double *xyz, double *normal,
						int *colour)
{
	t_obj_struct *elem;

	if (!(elem = create_obj_elem(xyz, normal, colour)))
		return (0);
	add_obj_elem(s, elem);
	return (1);
}
