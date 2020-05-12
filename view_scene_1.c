/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_scene_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 18:15:37 by ecross            #+#    #+#             */
/*   Updated: 2020/05/12 18:31:45 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*get_img_data(void *img_ptr, t_cam_struct *cam)
{
	int		bpp;
	int		ln;
	int		endian;
	void	*img_addr;

	img_addr = mlx_get_data_addr(img_ptr, &bpp, &ln, &endian);
	cam->bpp = bpp;
	cam->line_size = ln;
	return (img_addr);
}

int		str_match(char *str, char *real)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != real[i])
			return (0);
		i++;
	}
	if (str[i] != real[i])
		return (0);
	return (1);
}

int		check_args(int argc, char **argv)
{
	if (argc < 2 || argc > 4)
	{
		ft_putstr_fd("Incorrect args supplied\n", 1);
		return (0);
	}
	if (argc == 3 && !str_match(argv[2], "--save"))
	{
		ft_putstr_fd("Invalid second argument.", 1);
		ft_putstr_fd(" Use '--save' to save image as bmp.\n", 1);
		return (0);
	}
	return (1);
}

void	create_image_list(t_win_struct *ws, t_scene_struct *s)
{
	void			*img_ptr;
	char			*img_addr;
	t_cam_struct	*cam;

	cam = s->cam_list;
	while (cam)
	{
		img_ptr = mlx_new_image(ws->mlx_ptr, ws->res_x, ws->res_y);
		s->cam_curr = cam;
		img_addr = get_img_data(img_ptr, cam);
		draw_image(s, img_addr);
		add_img_to_list(ws, img_ptr, img_addr, cam);
		cam = cam->next;
	}
}

int		main(int argc, char **argv)
{
	t_scene_struct	s;
	t_win_struct	ws;

	if (!check_args(argc, argv))
		return (1);
	init_scene_struct(&s, 1);
	if (!parser(&s, argv[1]))
	{
		free_scene_struct(&s);
		return (1);
	}
	init_win_struct(&ws, s.res_xy[X], s.res_xy[Y]);
	if (!initialise_window(&ws))
	{
		ft_putstr_fd("Failed to initialise window.\n", 1);
		return (1);
	}
	create_image_list(&ws, &s);
	if (argc == 2)
		mlx_loop(ws.mlx_ptr);
	else if (argc == 3)
		bmp(&ws, ws.img_list);
	free_img_list(ws.img_list);
	free_scene_struct(&s);
}
