/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:48:39 by ecross            #+#    #+#             */
/*   Updated: 2019/10/15 17:40:21 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	if (str == NULL)
		return ((char*)str);
	while (*str)
	{
		if (*str == c)
			return ((char*)str);
		str++;
	}
	if (c == 0)
		return ((char*)str);
	return (0);
}
