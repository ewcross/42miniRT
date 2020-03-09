/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:20:50 by ecross            #+#    #+#             */
/*   Updated: 2020/03/09 15:04:10 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	free_img_list(t_img_struct *img)
{
	t_img_struct	*temp;

	while (img)
	{
		temp = img;
		img = img->next;
		//free(temp->img_ptr);
		free(temp->img_addr);
		free(temp);
	}
}

void	free_light_list(t_l_struct *light)
{
	t_l_struct	*temp;

	while (light)
	{
		temp = light;
		light = light->next;
		free(temp);
	}
}

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
