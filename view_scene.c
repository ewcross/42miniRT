/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:03:58 by ecross            #+#    #+#             */
/*   Updated: 2020/02/04 18:06:09 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	calc_vector_direction(double *ray_vector, double *cam_xyz, double *viewport_pix_xyz)
{
	ray_vector[X] = viewport_pix_xyz[X] - cam_xyz[X];
	ray_vector[Y] = viewport_pix_xyz[Y] - cam_xyz[Y];
	ray_vector[Z] = viewport_pix_xyz[Z] - cam_xyz[Z];
}

int main(void)
{
	int		x;
	int		y;
	double	distance_to_viewport;
	double	viewport_width;
	double	viewport_height;
	double	viewport_pix_xyz[3];
	double	ray_vector[3];
	scene_struct s;

	distance_to_viewport = 1;
	s.cam_xyz[X] = 0;
	s.cam_xyz[Y] = 0;
	s.cam_xyz[Z] = 0;
	s.cam_fov = 60;
	s.res_xy[X] = 1920;
	s.res_xy[Y] = 1080;

	viewport_width = (2 * tan((s.cam_fov * (M_PI / 180)) / 2) * distance_to_viewport);
	printf("viewport_width = %f\n", viewport_width);
	viewport_height = s.res_xy[Y] * (viewport_width / s.res_xy[X]);
	printf("viewport_height = %f\n", viewport_height);

	viewport_pix_xyz[Z] = distance_to_viewport;
	x = 1;
	printf("res_x = %f\n", s.res_xy[X]);
	printf("res_y = %f\n", s.res_xy[Y]);
	while (x < s.res_xy[X])
	{
		y = 1;
		while (y < s.res_xy[Y])
		{
			viewport_pix_xyz[X] = viewport_width * (x / s.res_xy[X]);
			viewport_pix_xyz[Y] = viewport_height * (y / s.res_xy[Y]);
			calc_vector_direction(ray_vector, s.cam_xyz, viewport_pix_xyz);
			y++;
		}
		x++;
	}
}
