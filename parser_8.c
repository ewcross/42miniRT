/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:13:57 by ecross            #+#    #+#             */
/*   Updated: 2020/05/12 17:57:31 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	fill_doubles(double *src, double *dst, int len)
{
	int	i;

	i = 0;
	if (!src)
	{
		while (i < len)
		{
			dst[i] = 0;
			i++;
		}
		return ;
	}
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

void	fill_ints(int *src, int *dst, int len)
{
	int	i;

	i = 0;
	if (!src)
	{
		while (i < len)
		{
			dst[i] = 0;
			i++;
		}
		return ;
	}
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}
