/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nums.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:23:49 by ecross            #+#    #+#             */
/*   Updated: 2020/01/30 14:24:00 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "mlx.h"
#include "libft.h"

int print_mouse_num(int button, int x, int y, void *param)
{
	ft_putchar_fd('-', 1);
	ft_putnbr_fd(button, 1);
	ft_putstr_fd(" at {", 1);
	ft_putnbr_fd(x, 1);
	ft_putchar_fd(',', 1);
	ft_putnbr_fd(y, 1);
	ft_putchar_fd('}', 1);
	ft_putchar_fd('\n', 1);
	return (0);
}

int print_key_num(int key_num, void *param)
{
	ft_putnbr_fd(key_num, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}

int main(void)
{
	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 300, "window");
	mlx_key_hook(win_ptr, print_key_num, (void*)0);
	mlx_mouse_hook(win_ptr, print_mouse_num, (void*)0);
	mlx_loop(mlx_ptr);
}
