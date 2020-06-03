/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:57:38 by ecross            #+#    #+#             */
/*   Updated: 2019/10/11 18:53:39 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned int i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char*)str1)[i] != ((unsigned char*)str2)[i])
		{
			return (((unsigned char*)str1)[i]
					- ((unsigned char*)str2)[i]);
		}
		i++;
	}
	return (0);
}
