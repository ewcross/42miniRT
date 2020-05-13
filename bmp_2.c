/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 16:05:04 by ecross            #+#    #+#             */
/*   Updated: 2020/05/13 08:19:01 by ecross           ###   ########.fr       */
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

int		fill_file_header(unsigned char *bmp, int fs)
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
