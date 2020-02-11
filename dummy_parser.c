/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 10:08:29 by ecross            #+#    #+#             */
/*   Updated: 2020/02/11 11:09:29 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	dummy_parser(t_scene_struct *s)
{
	s->res_xy[X] = 1000;
	s->res_xy[Y] = 625;
	s->viewport_distance = 1;
	
	s->cam_xyz[X] = 0;
	s->cam_xyz[Y] = 0;
	s->cam_xyz[Z] = 0;
	s->cam_fov = 60;
	
	s->ambient_ratio = 0.2;
	s->ambient_colour[X] = 0;
	s->ambient_colour[Y] = 0;
	s->ambient_colour[Z] = 0;

	s->light_xyz[X] = 15;
	s->light_xyz[Y] = 0;
	s->light_xyz[Z] = 0;
	s->light_brightness = 0.6;
	s->light_colour[X] = 255;
	s->light_colour[Y] = 255;
	s->light_colour[Z] = 255;
	
	s->sphere_xyz[X] = 0;
	s->sphere_xyz[Y] = 10;
	s->sphere_xyz[Z] = 50;
	s->sphere_diameter = 10;
	s->sphere_colour[R] = 0; 
	s->sphere_colour[G] = 255; 
	s->sphere_colour[B] = 0;

	s->plane_xyz[X] = 5;
	s->plane_xyz[Y] = 0;
	s->plane_xyz[Z] = 0;
	s->plane_normal[X] = 1;
	s->plane_normal[Y] = 0;
	s->plane_normal[Z] = 0;
	s->plane_colour[R] = 255; 
	s->plane_colour[G] = 100; 
	s->plane_colour[B] = 0;
}
