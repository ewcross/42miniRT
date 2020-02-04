/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:25:45 by ecross            #+#    #+#             */
/*   Updated: 2020/02/04 10:24:17 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "x11.h"
#include "header.h"

void add_line_to_img(void *win_struct)
{
	window_struct	*ws;
	char			*img_addr;
	int				bpp;
	int				line_size;
	int				endian;
	unsigned int	colour;

	ws = win_struct;
	img_addr = mlx_get_data_addr(ws->img_ptr, &bpp, &line_size, &endian);
	printf("bpp = %d\n", bpp);
	printf("line_size = %d\n", line_size);
	printf("endian = %d\n", endian);
	colour = mlx_get_color_value(ws->mlx_ptr, 0xff00);/*green*/
	printf("colour = %u\n", colour);
	*img_addr = 0;
	*(img_addr + 1) = 255;
	*(img_addr + 2) = 0;
	*(img_addr + 3) = 0;
}

int put_image(void *win_struct)
{
	window_struct *ws;

	ws = win_struct;
	mlx_put_image_to_window(ws->mlx_ptr, ws->win_ptr, ws->img_ptr, 400, 400);
	return (0);
}

int set_keys(int keycode, void *win_struct)
{
	window_struct *ws;

	ws = win_struct;
	if (keycode == 53)
	{
		mlx_destroy_window(ws->mlx_ptr, ws->win_ptr);
		exit(0);
	}
	if (keycode == 8)
		mlx_clear_window(ws->mlx_ptr, ws->win_ptr);
	return (0);
}

int close_program(void *win_struct)
{
	exit(0);
}

int main(void)
{
	window_struct win_struct;
	int win_size_x;
	int win_size_y;

	win_size_x = 1000;
	win_size_y = 1000;
	/*initialisation of connection, creation of window and hooks*/
	win_struct.mlx_ptr = mlx_init();
	win_struct.win_ptr = mlx_new_window(win_struct.mlx_ptr, win_size_x, win_size_y, "win");
	if (!win_struct.win_ptr)	/*need to initialise struct values*/
		return (1);
	mlx_hook(win_struct.win_ptr, DESTROYNOTIFY, NOEVENTMASK, close_program, 0);
	mlx_key_hook(win_struct.win_ptr, set_keys, &win_struct);
	mlx_loop(win_struct.mlx_ptr);
	/*creation of image with same size as window*/	
	win_struct.img_ptr = mlx_new_image(win_struct.mlx_ptr, win_size_x, win_size_y);
	/*create image contents*/
	//add_line_to_img(&win_struct);

	/*run loop*/
	mlx_loop_hook(win_struct.mlx_ptr, put_image, &win_struct);
	
	return (0);
}
