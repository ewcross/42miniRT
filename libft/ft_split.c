/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 18:33:36 by ecross            #+#    #+#             */
/*   Updated: 2019/10/16 13:27:31 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_sings(char const *s, char c)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			count++;
			i++;
			while (s[i] == c)
				i++;
		}
		else
			i++;
	}
	if (s[i - 1] == c)
		count--;
	return (count + 1);
}

static char		*add_sing(char const *s, int start, int end)
{
	int		i;
	char	*new_s;

	new_s = (char*)malloc(sizeof(char) * ((end - start) + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	while (start + i < end)
	{
		new_s[i] = s[start + i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

static int		extract_sings(char const *s, char c, char **output, int i)
{
	int marker;
	int count;

	count = 0;
	marker = i;
	while (s[i])
	{
		if (s[i] == c)
		{
			output[count] = add_sing(s, marker, i);
			count++;
			i++;
			while (s[i] == c)
				i++;
			marker = i;
		}
		else
			i++;
	}
	if (s[marker])
	{
		output[count] = add_sing(s, marker, i);
		count++;
	}
	return (count);
}

char			**ft_split(char const *s, char c)
{
	char	**output;
	int		i;
	int		count;

	if (s == NULL)
		return (NULL);
	output = (char**)malloc(sizeof(char*) * (count_sings(s, c) + 1));
	if (!output)
		return (NULL);
	i = 0;
	while (s[i] == c && s[i])
		i++;
	count = extract_sings(s, c, output, i);
	output[count] = 0;
	return (output);
}
