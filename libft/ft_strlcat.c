/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:13:49 by ecross            #+#    #+#             */
/*   Updated: 2019/10/15 17:49:50 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int i;
	unsigned int n;

	if (!dest || !src)
		return (0);
	n = 0;
	i = 0;
	while (dest[i] && i < size)
		i++;
	if (i != size)
	{
		while (i + n < size - 1 && src[n])
		{
			dest[i + n] = src[n];
			n++;
		}
		dest[i + n] = 0;
	}
	while (src[n])
		n++;
	return (i + n);
}
