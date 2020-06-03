/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:10:36 by ecross            #+#    #+#             */
/*   Updated: 2019/10/11 18:54:44 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t len)
{
	unsigned int	i;
	unsigned char	*ch_ptr;

	ch_ptr = ptr;
	i = 0;
	while (i < len)
	{
		ch_ptr[i] = c;
		i++;
	}
	return (ptr);
}
