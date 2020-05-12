/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_scene_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 18:15:50 by ecross            #+#    #+#             */
/*   Updated: 2020/05/12 18:31:51 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	get_ray_vec(double *ray_vec, double *v_w_h, int *xy, t_scene_struct *s)
{
	ray_vec[X] = (v_w_h[0] * ((double)xy[X] / s->res_xy[X])) - (v_w_h[0] / 2);
	ray_vec[Y] = (-1 * v_w_h[1] * ((double)xy[Y] / s->res_xy[Y]));
	ray_vec[Y] += (v_w_h[1] / 2);
	calc_unit_vec(ray_vec, ray_vec);
	rotate_ray(ray_vec, s->cam_curr);
}

void	get_pixel_colour(t_scene_struct *s, t_ray_struct *ray)
{
	const int	black[] = {0, 0, 0};
	double		i;
	double		light_adjust;
	t_l_struct	*light;

	if (ray->t_min == INFINITY)
	{
		fill_ints((int*)black, ray->colour, 3);
		return ;
	}
	fill_ints(ray->closest_obj->colour, ray->colour, 3);
	light_adjust = s->ambient_ratio;
	adj_cl(ray->colour, ray->closest_obj, s->ambient_colour, s->ambient_ratio);
	light = s->l_list;
	while (light)
	{
		s->l_curr = light;
		i = calc_light_intensity(s, ray->closest_obj, ray->ray_vec, ray->t_min);
		light_adjust += light->brightness * i;
		adj_cl(ray->colour, ray->closest_obj, light->colour, i);
		light = light->next;
	}
	scale_ints_vector(ray->colour, light_adjust, ray->colour);
}

int		trace_rays(t_scene_struct *s, void *img_addr, double *vp_w_h)
{
	int				xy[2];
	t_ray_struct	ray;

	ray.closest_obj = NULL;
	xy[X] = 0;
	while (xy[X] < s->res_xy[X])
	{
		xy[Y] = 0;
		while (xy[Y] < s->res_xy[Y])
		{
			ray.ray_vec[Z] = 1;
			get_ray_vec(ray.ray_vec, vp_w_h, xy, s);
			ray.closest_obj = find_closest_obj(&(ray.t_min), s, ray.ray_vec);
			get_pixel_colour(s, &ray);
			colour_img_pixel(img_addr, xy, s->cam_curr, ray.colour);
			xy[Y]++;
		}
		xy[X]++;
	}
	return (0);
}

int		draw_image(t_scene_struct *s, void *img_addr)
{
	double	vp_w_h[2];

	scale_light(s);
	vp_w_h[0] = (2 * tan((s->cam_curr->fov * (M_PI / 180)) / 2) * s->vp_dist);
	vp_w_h[1] = s->res_xy[Y] * (vp_w_h[0] / s->res_xy[X]);
	trace_rays(s, img_addr, vp_w_h);
	return (0);
}

void	add_img_to_list(t_win_struct *ws, void *img_ptr, char *img_addr,
							t_cam_struct *cam)
{
	t_img_struct	*elem;
	t_img_struct	*img_list;

	elem = (t_img_struct*)malloc(sizeof(t_img_struct));
	elem->img_ptr = img_ptr;
	elem->img_addr = img_addr;
	elem->next = NULL;
	elem->bpp = cam->bpp;
	elem->line_size = cam->line_size;
	if (!ws->img_list)
	{
		ws->img_list = elem;
		ws->first_img_addr = elem;
		return ;
	}
	img_list = ws->img_list;
	while (img_list->next)
		img_list = img_list->next;
	img_list->next = elem;
}
