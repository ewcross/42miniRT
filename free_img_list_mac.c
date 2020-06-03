/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_img_list_mac.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 10:35:04 by ecross            #+#    #+#             */
/*   Updated: 2020/05/21 10:35:19 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_img_list(t_img_struct *img)
{
	t_img_struct	*temp;

	while (img)
	{
		temp = img;
		img = img->next;
		free(temp->img_ptr);
		free(temp->img_addr);
		free(temp);
	}
}
