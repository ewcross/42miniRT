/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 14:13:44 by ecross            #+#    #+#             */
/*   Updated: 2020/05/25 11:23:55 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgnl.h"

int		gnl_rec(t_gnl *s_struct, char **line, int count)
{
	int		i_byt[2];
	int		ret;
	char	buff[BUFFER_SIZE];

	i_byt[1] = fill_buff(s_struct, buff);
	if (search(line, buff, &count, i_byt) < 0)
		return (i_byt[1]);
	if (i_byt[0] == i_byt[1] && i_byt[0] == BUFFER_SIZE)
		ret = gnl_rec(s_struct, line, count);
	else
	{
		if (!(*line = make(s_struct, buff, count, i_byt)))
			return (-1);
		ret = 1;
	}
	if (ret == -2)
		if (!(*line = make(s_struct, buff, count, i_byt)))
			return (-1);
	if ((i_byt[0] == i_byt[1] && i_byt[0] != BUFFER_SIZE) || ret == -2)
		ret = 0;
	write_backwards(*line, buff, i_byt[0], count);
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	int				ret;
	static t_gnl	s_struct;

	if (!line || fd < 0)
		return (-1);
	*line = NULL;
	s_struct.fd = fd;
	s_struct.processed = 0;
	ret = gnl_rec(&s_struct, line, 0);
	if (ret == -2)
		return (0);
	return (ret);
}
