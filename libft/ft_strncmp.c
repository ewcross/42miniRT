/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:14:55 by ecross            #+#    #+#             */
/*   Updated: 2019/10/15 18:05:57 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (i == n - 1)
			return (0);
		i++;
	}
	if (s2[i] != 0)
		return (-(unsigned char)s2[i]);
	if (s1[i] != 0)
		return ((unsigned char)s1[i]);
	return (0);
}
