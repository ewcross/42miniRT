/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:17:21 by ecross            #+#    #+#             */
/*   Updated: 2019/10/14 11:32:51 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_mem_size(int nb)
{
	int mem_size;

	if (nb == 0)
		return (1);
	mem_size = 0;
	if (nb < 0)
		mem_size++;
	while (nb)
	{
		mem_size++;
		nb /= 10;
	}
	return (mem_size);
}

char		*ft_itoa(int n)
{
	int		mem_size;
	long	num;
	char	*str;

	num = n;
	mem_size = get_mem_size(n);
	str = (char*)malloc(sizeof(char) * (mem_size + 1));
	if (str == NULL)
		return (NULL);
	str[mem_size--] = 0;
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	while (num > 9)
	{
		str[mem_size--] = (num % 10) + 48;
		num /= 10;
	}
	str[mem_size] = (num % 10) + 48;
	return (str);
}
