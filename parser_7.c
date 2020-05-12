/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:13:52 by ecross            #+#    #+#             */
/*   Updated: 2020/05/12 17:56:44 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		simple_atoi(char *str)
{
	int output;

	if (!str || !(*str))
		return (-1);
	output = 0;
	while (*str > 47 && *str < 58)
	{
		output = (*str - 48) + (output * 10);
		str++;
	}
	if (!(*str))
		return (output);
	else
		return (-1);
}

double	tenths(char *str)
{
	int	i;
	int end_index;

	end_index = 0;
	while (str[end_index])
		end_index++;
	i = 0;
	while (str[i] != '.' && str[i])
		i++;
	if (str[i] == '.')
		return ((double)(pow(0.1, end_index - i - 1)));
	return (1);
}

int		ft_atof(char *str, double *fl)
{
	double	output;
	int		neg;
	char	*str_copy;

	str_copy = str;
	if (!str || !(*str))
		return (-1);
	output = 0;
	neg = 1;
	if (*str == '-' || *str == '+')
		neg = 44 - *str++;
	while ((*str > 47 && *str < 58) || *str == '.')
	{
		if (*str != '.')
			output = (*str - 48) + (output * 10);
		str++;
	}
	if (*str)
		return (-1);
	*fl = output * neg * tenths(str_copy);
	return (0);
}

int		get_colour(char *str, int *colour)
{
	int		i;
	char	**strs;

	strs = ft_split(str, ',');
	if (len_str_arr(strs) != 3)
		return (-6);
	i = 0;
	while (i < 3)
	{
		if ((colour[i] = simple_atoi(strs[i])) == -1 || colour[i] > 255)
			return (-6);
		i++;
	}
	free_strs(strs);
	return (0);
}

int		get_data(char *str, double *data)
{
	if (ft_atof(str, data) == -1 || *data <= 0)
		return (-5);
	return (0);
}
