/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 10:40:13 by ecross            #+#    #+#             */
/*   Updated: 2020/05/15 10:48:51 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include "mlx.h"
# include "x11.h"

int	main(void)
{
	int	x;
	int	y;
	int	res;
	void	*mlx_ptr;

	mlx_ptr = mlx_init();
	res = mlx_get_screen_size(mlx_ptr, x, y);
	printf("got x = %d, y = %d and returned %d\n", x, y, res);
}
