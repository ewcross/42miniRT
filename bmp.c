/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:01:11 by ecross            #+#    #+#             */
/*   Updated: 2020/03/05 13:04:42 by ecross           ###   ########.fr       */
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

int		fill_file_header(t_win_struct *ws, unsigned char *bmp, int bpp)
{
	int		i;
	int		n;
	int		fs;

	fs = BMP_HEADER_SIZE + BMP_INFO_SIZE + (ws->res_x * ws->res_y * (bpp / 8));
	printf("file size = %d\n", fs);
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

int		create_bmp(t_win_struct *ws, t_img_struct *img, int id)
{
	int				bpp;
	int				line_size;
	int				endian;
	unsigned char	*bmp;
	void			*img_addr;

	/*img_addr = mlx_get_data_addr(img->img_ptr, &bpp, &line_size, &endian);*/
	/*bmp = (char*)malloc(BMP_HEADER_SIZE + BMP_INFO_SIZE + (ws->res_x * ws->res_y * (bpp / 8)));*/
	bpp = 32;
	bmp = (unsigned char*)malloc(54);
	if (!bmp)
	{
		ft_putstr_fd("Could not generate bmp file for image ", 1);
		ft_putstr_fd(ft_itoa(id + 1), 1);
		ft_putstr_fd(".\n", 1);
		return (0);
	}
	fill_info_header(ws, bmp, fill_file_header(ws, bmp, bpp), bpp);
	int i = 0;
	while (i < 14)
	{
		printf("%d, ", *(bmp + i));
		i++;
	}
	while (i < 54)
	{
		if (!((i - 2) % 4))
			printf("\n");
		printf("%d, ", *(bmp + i));
		i++;
	}
	printf("\n");
	/*fill_pixel_data(bmp, img);*/
	free(bmp);
	return (1);
}

void	bmp(t_win_struct *ws, t_img_struct *img)
{
	int		id;

	id = 0;
	create_bmp(ws, img, id);
	while (img)
	{
		/*create_bmp(ws, img, id);*/
		id++;
		img = img->next;
	}
	return ;
}
/*
int	main(void)
{
	t_win_struct	ws;

	ws.res_x = 1000;
	ws.res_y = 650;
	bmp(&ws, NULL);
	return (0);
}*/
