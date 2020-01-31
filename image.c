/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 17:47:07 by ecross            #+#    #+#             */
/*   Updated: 2020/01/31 17:47:09 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	put_circle(t_struct *ws, int x, int y, int colour)
{
	float r;
	float th;

	r = 40;
	while (r > 0)
	{
		th = 0;
		while (th < 360)
		{
			mlx_pixel_put(ws->mlx_ptr, ws->win_ptr, x + (r * cos(th)), y + (r * sin(th)), colour);
			th += 0.5;
		}
		r -= 0.5;
	}
}

int draw_circle(void *win_struct)
{
	t_struct *ws;
	
	ws = win_struct;
	put_circle(ws, 200, 200, 0xffff00);
	put_circle(ws, 300, 200, mlx_get_color_value(ws->mlx_ptr, 0xffff00));
	return (0);
}
