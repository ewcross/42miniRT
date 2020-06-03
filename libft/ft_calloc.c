/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:44:22 by ecross            #+#    #+#             */
/*   Updated: 2019/10/15 17:47:38 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned int	i;
	unsigned char	*point;

	point = (unsigned char*)malloc(count * size);
	if (!point)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		*(point + i) = 0;
		i++;
	}
	return ((void*)point);
}
