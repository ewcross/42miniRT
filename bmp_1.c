/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 16:00:32 by ecross            #+#    #+#             */
/*   Updated: 2020/05/21 16:04:39 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	fill_pixel_data(char *img_addr, unsigned char *bmp, int img_size,
							int line_length)
{
	int	i;
	int	n;
	int	last_line;

	last_line = 54 + img_size - line_length;
	i = 0;
	while (i < img_size)
	{
		n = 0;
		while (n < line_length)
		{
			bmp[last_line - i + n] = img_addr[i + n];
			n++;
		}
		i += line_length;
	}
}

char	*name_maker(char *name, int id)
{
	char	*file_name;
	char	*p1;
	char	**strs;

	strs = ft_split(name, '/');
	file_name = strs[len_str_arr(strs) - 1];
	file_name = ft_strdup(file_name);
	free_strs(strs);
	strs = ft_split(file_name, '.');
	free(file_name);
	file_name = strs[0];
	file_name = ft_strdup(file_name);
	free_strs(strs);
	if (id)
	{
		p1 = ft_strjoin(file_name, "_");
		free(file_name);
		file_name = ft_strjoin(p1, ft_itoa(id));
		free(p1);
	}
	p1 = ft_strjoin(file_name, ".bmp");
	free(file_name);
	return (p1);
}

int		create_bmp_file(char *name, unsigned char *bmp, int id, int fs)
{
	int		fd;
	char	*file_name;

	file_name = name_maker(name, id);
	fd = open(file_name, O_WRONLY | O_CREAT, 0777);
	if (fd < 0)
	{
		ft_putstr_fd("Error creating one or more image bmp files.\n", 1);
		return (0);
	}
	write(fd, bmp, fs);
	free(file_name);
	return (1);
}

int		create_bmp(char *name, t_win_struct *ws, t_img_struct *img, int id)
{
	int				i;
	int				fs;
	int				line_length;
	unsigned char	*bmp;

	fs = BMP_HEADER_SIZE + BMP_INFO_SIZE;
	fs += (ws->res_x * ws->res_y * (img->bpp / 8));
	bmp = (unsigned char*)malloc(fs);
	if (!bmp)
	{
		ft_putstr_fd("Could not generate bmp file for image ", 1);
		ft_putstr_fd(ft_itoa(id + 1), 1);
		ft_putstr_fd(".\n", 1);
		return (0);
	}
	i = fill_info_header(ws, bmp, fill_file_header(bmp, fs), img->bpp);
	line_length = ws->res_x * (img->bpp / 8);
	fill_pixel_data(img->img_addr, bmp, fs - i, line_length);
	create_bmp_file(name, bmp, id, fs);
	free(bmp);
	return (1);
}

void	bmp(char *name, t_win_struct *ws, t_img_struct *img)
{
	int		id;

	id = 0;
	while (img)
	{
		create_bmp(name, ws, img, id);
		id++;
		img = img->next;
	}
	return ;
}
