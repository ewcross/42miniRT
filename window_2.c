/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 18:25:28 by ecross            #+#    #+#             */
/*   Updated: 2020/05/12 18:30:56 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		put_image(void *window_struct)
{
	void			*img_ptr;
	t_win_struct	*ws;

	ws = window_struct;
	img_ptr = ws->img_list->img_ptr;
	if (!img_ptr)
		return (0);
	mlx_put_image_to_window(ws->mlx_ptr, ws->win_ptr, img_ptr, 0, 0);
	return (1);
}

void	shift_next_cam(t_win_struct *ws)
{
	ws->img_list = ws->img_list->next;
	if (!ws->img_list)
		ws->img_list = ws->first_img_addr;
	mlx_loop_hook(ws->mlx_ptr, put_image, ws);
}
