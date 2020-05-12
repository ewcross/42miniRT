/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 16:16:36 by ecross            #+#    #+#             */
/*   Updated: 2020/05/12 16:16:47 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_cam_list(t_cam_struct *cam)
{
	t_cam_struct	*temp;

	while (cam)
	{
		temp = cam;
		cam = cam->next;
		free(temp);
	}
}

void	free_obj_list(t_obj_struct *obj)
{
	t_obj_struct	*temp;

	while (obj)
	{
		temp = obj;
		obj = obj->next;
		free(temp);
	}
}

void	free_scene_struct(t_scene_struct *s)
{
	free_obj_list(s->obj_list);
	free_cam_list(s->cam_list);
	free_light_list(s->l_list);
}
