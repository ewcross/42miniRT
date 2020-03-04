/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:01:11 by ecross            #+#    #+#             */
/*   Updated: 2020/03/04 18:29:00 by ecross           ###   ########.fr       */
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

int		fill_metadata(char *bmp)
{
	int		i;
	int		n;
	char	bin[4][8];

	i = 0;
	bmp[i++] = 'B';
	bmp[i++] = 'M';
	/*file size as int in little endian*/
	int_to_binary(bin, 2500000);
	n = 0;
	while (n < 4)
	{
		bmp[i++] = binary_to_int(bin[3 - n]);
		n++;
	}
	/*some defaults all set to 0*/
	n = 0;
	while (n < 4)
	{
		bmp[i++] = 0;
		n++;
	}
	/*pixel offset (= 54) as int in little endian*/
	n = 0;
	while (n < 3)
	{
		bmp[i++] = 0;
		n++;
	}
	bmp[i++] = BMP_HEADER_SIZE + BMP_INFO_SIZE;
	return (i);
}

int		create_bmp(t_img_struct *img, int id, int res_x, int res_y)
{
	int		bpp;
	int		line_size;
	int		endian;
	char	*bmp;
	void	*img_addr;

	/*img_addr = mlx_get_data_addr(img->img_ptr, &bpp, &line_size, &endian);*/
	/*bmp = (char*)malloc(BMP_HEADER_SIZE + BMP_INFO_SIZE + (res_x * res_y));*/
	bmp = (char*)malloc(14);
	if (!bmp)
	{
		ft_putstr_fd("Could not generate bmp file for image ", 1);
		ft_putstr_fd(ft_itoa(id + 1), 1);
		ft_putstr_fd(".\n", 1);
		return (0);
	}
	fill_metadata(bmp);
	i = 0;
	while (i < 14)
	{
		write(1, *(bmp + i) + 48, 1);
		write(1, ",", 1);
		i++;
	}
	/*fill_pixel_data(bmp, img);*/
	free(bmp);
	return (1);
}

void	bmp(t_win_struct *ws, t_img_struct *img)
{
	int		id;

	id = 0;
	create_bmp(img, id, 0, 0);
	while (img)
	{
		/*create_bmp(img, id, ws->res_x, ws->res_y);*/
		id++;
		img = img->next;
	}
	return ;
}

int	main(void)
{
	bmp(NULL, NULL);
	return (0);
}
