/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:56:27 by ecross            #+#    #+#             */
/*   Updated: 2020/05/25 11:23:50 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgnl.h"

int		move_chars(char *src, char *dest, int start, int end)
{
	int i;

	i = 0;
	while (i + start < end)
	{
		dest[i] = src[i + start];
		i++;
	}
	return (i);
}

void	write_backwards(char *line, char *buff, int n, int count)
{
	int i;

	i = 0;
	while (i < n)
	{
		line[count - i - 1] = buff[n - i - 1];
		i++;
	}
}

int		fill_buff(t_gnl *s_struct, char *buff)
{
	int bytes;
	int n_chars;

	n_chars = s_struct->n_chars;
	if (s_struct->processed == 0 && n_chars)
	{
		move_chars(s_struct->res_chars, buff, 0, n_chars);
		s_struct->processed = 1;
		bytes = read(s_struct->fd, buff + n_chars, BUFFER_SIZE - n_chars);
		if (bytes == -1)
			return (-1);
		bytes += n_chars;
	}
	else
	{
		bytes = read(s_struct->fd, buff, BUFFER_SIZE);
		if (bytes == -1)
			return (-1);
		if (bytes == 0 && n_chars == 0)
			return (-2);
	}
	return (bytes);
}

char	*make(t_gnl *s_struct, char *buff, int count, int *i_byt)
{
	int		chrs;
	char	*line;

	line = (char*)malloc(count + 1);
	if (line == NULL)
		return (NULL);
	line[count] = 0;
	if (i_byt[1])
	{
		chrs = move_chars(buff, s_struct->res_chars, (i_byt[0] + 1), i_byt[1]);
		s_struct->n_chars = chrs;
	}
	else
		s_struct->n_chars = 0;
	s_struct->processed = 0;
	return (line);
}

int		search(char **line, char *buff, int *addr_count, int *i_byt)
{
	if (i_byt[1] == -1 || i_byt[1] == -2)
	{
		if (*addr_count == 0)
		{
			if (!(*line = (char*)malloc(1)))
				return (-1);
			(*line)[0] = 0;
			return (i_byt[1]);
		}
	}
	i_byt[0] = 0;
	while (i_byt[0] < i_byt[1])
	{
		if (buff[i_byt[0]] == 10)
			break ;
		i_byt[0]++;
	}
	*addr_count += i_byt[0];
	return (i_byt[1]);
}
