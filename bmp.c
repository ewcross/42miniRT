/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:01:11 by ecross            #+#    #+#             */
/*   Updated: 2020/03/06 12:21:18 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	int_to_binary(char buff[4][8], int num)
{
	int i;

	i = 31;
	while (num)
	{
		buff[i / 8][i % 8] = (num % 2) + 48;
		i--;
		num /= 2;
	}
	while (i)
	{
		buff[i / 8][i % 8] = 0 + 48;
		i--;
	}
	buff[i / 8][i % 8] = 0 + 48;
}

int		binary_to_int(char binary[8])
{
	int		i;
	int		output;

	output = 0;
	i = 0;
	while (i < 8)
	{
		output = (output * 2) + (binary[i] - 48);
		i++;
	}
	return (output);
}
	
int		fill_little_endian(unsigned char *bmp, int num, int i)
{
	int		n;
	char	bin[4][8];

	int_to_binary(bin, num);
	n = 0;
	while (n < 4)
	{
		bmp[i++] = binary_to_int(bin[3 - n]);
		n++;
	}
	return (i);
}

int		fill_info_header(t_win_struct *ws, unsigned char *bmp, int i, int bpp)
{
	int	n;

	i = fill_little_endian(bmp, BMP_INFO_SIZE, i);
	i = fill_little_endian(bmp, ws->res_x, i);
	i = fill_little_endian(bmp, ws->res_y, i);
	bmp[i++] = 1;
	bmp[i++] = 0;
	bmp[i++] = bpp;
	bmp[i++] = 0;
	n = 0;
	while (n < 24)
	{
		bmp[i++] = 0;
		n++;
	}
	return (i);
}

int		fill_file_header(t_win_struct *ws, unsigned char *bmp, int fs)
{
	int		i;
	int		n;

	i = 0;
	bmp[i++] = 'B';
	bmp[i++] = 'M';
	i = fill_little_endian(bmp, fs, i);
	n = 0;
	while (n < 4)
	{
		bmp[i++] = 0;
		n++;
	}
	i = fill_little_endian(bmp, BMP_HEADER_SIZE + BMP_INFO_SIZE, i);
	return (i);
}

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

	fs = BMP_HEADER_SIZE + BMP_INFO_SIZE + (ws->res_x * ws->res_y * (img->bpp / 8));
	bmp = (unsigned char*)malloc(fs);
	if (!bmp)
	{
		ft_putstr_fd("Could not generate bmp file for image ", 1);
		ft_putstr_fd(ft_itoa(id + 1), 1);
		ft_putstr_fd(".\n", 1);
		return (0);
	}
	i = fill_info_header(ws, bmp, fill_file_header(ws, bmp, fs), img->bpp);
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
