/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:20:50 by ecross            #+#    #+#             */
/*   Updated: 2020/05/12 16:16:19 by ecross           ###   ########.fr       */
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
