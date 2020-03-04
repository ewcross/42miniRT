/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:01:11 by ecross            #+#    #+#             */
/*   Updated: 2020/03/04 12:11:39 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	create_bmp(t_img_struct *img)
{
	int		bpp;
	int		line_size;
	int		endian;
	void	*img_addr;

	img_addr = mlx_get_data_addr(img_ptr, &bpp, &line_size, &endian);
}

void	bmp(t_img_struct *img)
{
	int		id;

	id = 0;
	while (img)
	{
		create_bmp(img, id);
		id++;
		img = img->next;
	}
}
