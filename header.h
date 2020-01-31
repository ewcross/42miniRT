/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:31:30 by ecross            #+#    #+#             */
/*   Updated: 2020/01/31 14:48:29 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

typedef struct	s_struct
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
}				t_struct;

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "mlx.h"
#include "libft.h"

int		set_keys(int keycode, void *win_struct);
int		draw_circle(void *win_struct);
void	put_circle(t_struct *ws, int x, int y, int colour);

#endif
