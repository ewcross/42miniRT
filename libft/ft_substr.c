/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:54:35 by ecross            #+#    #+#             */
/*   Updated: 2019/10/15 18:02:26 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(char const *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char		*ft_substr(char const *str, unsigned int start, size_t len)
{
	int		i;
	int		size;
	char	*new_str;

	if (str == NULL)
		return (NULL);
	if (start > (unsigned int)get_len(str) - 1)
		return ("");
	i = start;
	while (i - start < len && str[i])
		i++;
	size = i - start;
	new_str = (char*)malloc(sizeof(char) * (size + 1));
	if (new_str == NULL)
		return (NULL);
	new_str[size] = 0;
	i = 0;
	while (i < size)
	{
		new_str[i] = str[start + i];
		i++;
	}
	return (new_str);
}
