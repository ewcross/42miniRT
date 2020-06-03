/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:48:21 by ecross            #+#    #+#             */
/*   Updated: 2019/10/11 18:48:33 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char *ch_point;

	if (str == NULL)
		return (NULL);
	ch_point = 0;
	while (*str)
	{
		if (*str == c)
			ch_point = (char*)str;
		str++;
	}
	if (c == 0)
		return ((char*)str);
	return (ch_point);
}
