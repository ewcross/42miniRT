/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:19:32 by ecross            #+#    #+#             */
/*   Updated: 2019/10/11 18:57:20 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	unsigned int i;
	unsigned int n;

	if (str == NULL || find == NULL)
		return (NULL);
	if (find[0] == 0)
		return ((char*)str);
	i = 0;
	while (str[i] && i < len)
	{
		if (find[0] == str[i])
		{
			n = 0;
			while (find[n] == str[i + n] && find[n]
					&& i + n < len)
				n++;
			if (find[n] == 0)
				return ((char*)(str + i));
		}
		i++;
	}
	return (0);
}
