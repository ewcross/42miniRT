/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 11:56:27 by ecross            #+#    #+#             */
/*   Updated: 2020/02/25 18:28:23 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "structs.h"

int put_image(void *window_struct)
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

void	shift_prev_cam(t_win_struct *ws)
{
	t_img_struct	*temp;
	
	if (ws->img_list == ws->first_img_addr)
		while (ws->img_list->next)
			ws->img_list = ws->img_list->next;
	else
	{
		temp = ws->img_list;
		ws->img_list = ws->first_img_addr;
		while (ws->img_list->next != temp)
			ws->img_list = ws->img_list->next;
	}
	mlx_loop_hook(ws->mlx_ptr, put_image, ws);
}

int set_keys(int keycode, void *window_struct)
{
	t_win_struct	*ws;

	ws = window_struct;
	if (keycode == 53)
	{
		mlx_destroy_window(ws->mlx_ptr, ws->win_ptr);
		exit(0);
	}
	if (keycode == 8)
		mlx_clear_window(ws->mlx_ptr, ws->win_ptr);
	if (keycode == 124)
		shift_next_cam(ws);
	if (keycode == 123)
		shift_prev_cam(ws);
	return (0);
}

int close_program(void *window_struct)
{
	(void)window_struct;
	exit(0);
}

int initialise_window(t_win_struct *ws)
{
	ws->mlx_ptr = mlx_init();
	ws->win_ptr = mlx_new_window(ws->mlx_ptr, ws->res_x, ws->res_y, "window");
	if (!ws->win_ptr)
		return (0);
	mlx_hook(ws->win_ptr, DESTROYNOTIFY, NOEVENTMASK, close_program, 0);
	mlx_key_hook(ws->win_ptr, set_keys, ws);
	mlx_loop_hook(ws->mlx_ptr, put_image, ws);
	return (1);
}

void	colour_img_pixel(char *img_addr, int *xy, t_cam_struct *cam, int *colour)
{
	int	pixel_index;

	pixel_index = (xy[X] * (cam->bpp / 8)) + (cam->line_size * xy[Y]);
	*(img_addr + pixel_index) = colour[B];
	*(img_addr + pixel_index + 1) = colour[G];
	*(img_addr + pixel_index + 2) = colour[R];
}
