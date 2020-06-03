/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:39:25 by ecross            #+#    #+#             */
/*   Updated: 2019/10/11 18:47:24 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	size;
	char			*new_str;

	if (s == NULL)
		return (NULL);
	size = 0;
	while (s[size])
		size++;
	new_str = (char*)malloc(size + 1);
	if (new_str == NULL)
		return (NULL);
	new_str[size] = 0;
	size = 0;
	while (s[size])
	{
		new_str[size] = f(size, s[size]);
		size++;
	}
	return (new_str);
}
