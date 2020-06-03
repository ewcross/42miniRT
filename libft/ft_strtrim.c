/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 10:33:00 by ecross            #+#    #+#             */
/*   Updated: 2019/10/11 18:48:36 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(char ch, char const *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (ch == set[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*trim_string(char const *str, int start_index, int end_index)
{
	int		i;
	int		size;
	char	*new_str;

	size = end_index - start_index + 1;
	new_str = (char*)malloc(size + 1);
	if (new_str == NULL)
		return (NULL);
	new_str[size] = 0;
	i = 0;
	while (i < size)
	{
		new_str[i] = str[start_index + i];
		i++;
	}
	return (new_str);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int start_index;
	int end_index;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start_index = 0;
	end_index = 0;
	while (s1[end_index])
		end_index++;
	end_index -= 1;
	while (is_in(s1[start_index], set))
		start_index++;
	if (s1[start_index] == 0)
		return (trim_string(s1, start_index, start_index));
	while (is_in(s1[end_index], set))
		end_index--;
	return (trim_string(s1, start_index, end_index));
}
