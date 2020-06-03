/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:26:57 by ecross            #+#    #+#             */
/*   Updated: 2019/10/14 11:21:13 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int i;
	int output;
	int neg;

	i = 0;
	output = 0;
	neg = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		neg *= 44 - str[i];
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		output = (output * 10) + (str[i] - 48);
		i++;
	}
	return (output * neg);
}
