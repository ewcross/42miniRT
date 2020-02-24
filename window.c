/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 11:56:27 by ecross            #+#    #+#             */
/*   Updated: 2020/02/24 13:13:05 by ecross           ###   ########.fr       */
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

int set_keys(int keycode, void *window_struct)
{
	t_win_struct	*ws;
	t_img_struct	*first_img;
	t_img_struct	*temp;

	ws = window_struct;
	if (keycode == 53)
	{
		mlx_destroy_window(ws->mlx_ptr, ws->win_ptr);
		exit(0);
	}
	if (keycode == 8)
		mlx_clear_window(ws->mlx_ptr, ws->win_ptr);
	if (keycode == 124)
	{
		ws->img_list = ws->img_list->next;
		if (!ws->img_list)
			ws->img_list = ws->first_img_addr;
		mlx_loop_hook(ws->mlx_ptr, put_image, ws);
		//mlx_destroy_image(ws->mlx_ptr, temp->img_ptr);
		//temp = img->next;
		/*destroy current image - maybe do not do this if it frees
		  all the memory storing image - only want to remove from screen*/
		//mlx_put_image_to_window(ws->mlx_ptr, ws->win_ptr, temp->img_ptr, 0, 0);
	}
	//if (keycode == 123)
	//{
		/*destroy current image - maybe do not do this if it frees
		  all the memory storing image - only want to remove from screen*/
	//}
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

void	colour_img_pixel(char *img_addr, int x, int y, int bpp, int line_size, int *colour)
{
	int	pixel_index;

	pixel_index = (x * (bpp / 8)) + ((line_size) * y);
	*(img_addr + pixel_index) = colour[B];
	*(img_addr + pixel_index + 1) = colour[G];
	*(img_addr + pixel_index + 2) = colour[R];
}
