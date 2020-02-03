/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:18:57 by ecross            #+#    #+#             */
/*   Updated: 2020/02/03 19:08:09 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	simple_atoi(char *str)
{
	int output;

	output = 0;
	while(*str > 47 && *str < 58)
	{
		output = (*str - 48) + (output * 10);
		str++;
	}
	if (!(*str))
		return (output);
	else
		return (-1);
}

int	len_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i])
		i++;
	return (i);
}

/*should find and R and two strings of only digits, separated by only spaces*/

int	R_func(char *line)
{
	int		res_x;
	int		res_y;
	char	**strs;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 3)
		return (-1);
	res_x = simple_atoi(strs[1]);
	res_y = simple_atoi(strs[2]);
	printf("res_x = %d\n", res_x);
	printf("res_y = %d\n", res_y);
	if (res_x < 1 || res_y < 1)
		return (-1);
	return (0);
}

int	A_func(char *line)
{
	char	**strs;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 3)
		return (-1);
	return (0);
}

int	c_func(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i + 1] == ' ')
		return(cam_func(line));
	else if (line[i + 1] == 'y')
		return(cy_func(line));
	else
		return (-1);
}

int	l_func(char *line)
{
	char	**strs;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-1);
	return (0);
}

int	s_func(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i + 1] == 'p')
		return(sp_func(line));
	else if (line[i + 1] == 'q')
		return(sq_func(line));
	else
		return (-1);
}

int	p_func(char *line)
{
	char	**strs;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-1);
	return (0);
}

int	t_func(char *line)
{
	char	**strs;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 5)
		return (-1);
	return (0);
}

int	cam_func(char *line)
{
	char	**strs;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-1);
	return (0);
}

int	cy_func(char *line)
{
	char	**strs;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 6)
		return (-1);
	return (0);
}

int	sp_func(char *line)
{
	char	**strs;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-1);
	return (0);
}

int	sq_func(char *line)
{
	char	**strs;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 5)
		return (-1);
	return (0);
}
