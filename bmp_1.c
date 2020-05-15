/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 16:00:32 by ecross            #+#    #+#             */
/*   Updated: 2020/05/13 08:40:34 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	fill_pixel_data(char *img_addr, unsigned char *bmp, int i, int fs)
{
	int		n;

	n = 0;
	while (n < fs - i)
	{
		bmp[n + i] = img_addr[n];
		n++;
	}
}

int		create_bmp_file(unsigned char *bmp, int id, int fs)
{
	int		fd;
	char	*file_name;
	char	*p1;

	if (!id)
		file_name = "image.bmp";
	else
	{
		p1 = ft_strjoin("image_", ft_itoa(id));
		file_name = ft_strjoin(p1, ".bmp");
		free(p1);
	}
	fd = open(file_name, O_WRONLY | O_CREAT, 0777);
	if (fd < 0)
	{
		ft_putstr_fd("Error creating one or more image bmp files.\n", 1);
		return (0);
	}
	write(fd, bmp, fs);
	if (id)
		free(file_name);
	return (1);
}

int		create_bmp(t_win_struct *ws, t_img_struct *img, int id)
{
	int				i;
	int				fs;
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
	fill_pixel_data(img->img_addr, bmp, i, fs);
	create_bmp_file(bmp, id, fs);
	free(bmp);
	return (1);
}

void	bmp(t_win_struct *ws, t_img_struct *img)
{
	int		id;

	id = 0;
	while (img)
	{
		create_bmp(ws, img, id);
		id++;
		img = img->next;
	}
	return ;
}
