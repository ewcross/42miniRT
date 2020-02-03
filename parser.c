/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:14:09 by ecross            #+#    #+#             */
/*   Updated: 2020/02/03 19:00:13 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		pos_in_set(char ch, char *set)
{
	int i;

	if (ch == 0)
		return (-1);
	i = 0;
	while (set[i])
	{
		if (ch == set[i])
			return (i);
		i++;
	}
	return (-1);
}

void	init_func_arr(int (*func_arr[])(char *))
{
	func_arr[0] = R_func;
	func_arr[1] = A_func;
	func_arr[2] = c_func;
	func_arr[3] = l_func;
	func_arr[4] = s_func;
	func_arr[5] = p_func;
	func_arr[6] = t_func;
}

int		parse_line(char *line)
{
	int		i;
	int		pos;
	int		(*func_arr[7])(char *);

	init_func_arr(func_arr);
	i = 0;
	while (line[i] == ' ')
		i++;
	if ((pos = pos_in_set(line[i], CHARSET)) > -1)
		return(func_arr[pos](line));
	else
		return (-1);
}

int main(int argc, char **argv)
{
	char *line;

	line = argv[1];
	if (parse_line(line))
		printf("check line: \"%s\"\n", line);
	return (0);
}
