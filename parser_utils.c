/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:18:57 by ecross            #+#    #+#             */
/*   Updated: 2020/02/26 08:33:43 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "structs.h"

/*ERRORS TO HANDLE*/

/*normal of 0,0,0
  negative dimensions
  negative resolution
  all normals should be normalised here and then where this happens
  elsewhere can be removed*/

void	fill_doubles(double *src, double *dst, int len)
{
	int	i;

	i = 0;
	if (!src)
	{
		while (i < len)
		{	
			dst[i] = 0;
			i++;
		}
		return ;
	}
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

void	fill_ints(int *src, int *dst, int len)
{
	int	i;

	i = 0;
	if (!src)
	{
		while (i < len)
		{	
			dst[i] = 0;
			i++;
		}
		return ;
	}
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

t_obj_struct	*create_obj_elem(char id, double *xyz, double *normal, int *colour)
{
	t_obj_struct *elem;

	if(!(elem = (t_obj_struct*)malloc(sizeof(t_obj_struct))))
		return (NULL);
	elem->id = id;
	fill_doubles(xyz, elem->xyz, 3);
	fill_doubles(normal, elem->normal, 3);
	fill_ints(colour, elem->colour, 3);
	elem->next = NULL;
	return (elem);
}

t_cam_struct	*create_cam_elem(double *xyz, double *normal, double fov)
{
	t_cam_struct *elem;

	if(!(elem = (t_cam_struct*)malloc(sizeof(t_cam_struct))))
		return (NULL);
	fill_doubles(xyz, elem->xyz, 3);
	fill_doubles(normal, elem->normal, 3);
	elem->fov = fov;
	elem->next = NULL;
	return (elem);
}

t_l_struct	*create_l_elem(double *xyz, double brightness, int *colour)
{
	t_l_struct *elem;

	if(!(elem = (t_l_struct*)malloc(sizeof(t_l_struct))))
		return (NULL);
	fill_doubles(xyz, elem->xyz, 3);
	fill_ints(colour, elem->colour, 3);
	elem->brightness = brightness;
	elem->next = NULL;
	return (elem);
}

void	add_obj_elem(t_scene_struct *s, t_obj_struct *elem)
{
	t_obj_struct *temp;

	if (!s->obj_list)
	{
		s->obj_list = elem;
		return ;
	}
	temp = s->obj_list;
	while (temp->next)
		temp = temp->next;
	temp->next = elem;
}

void	add_cam_elem(t_scene_struct *s, t_cam_struct *elem)
{
	t_cam_struct *temp;

	temp = s->cam_list;
	if (!temp)
	{
		s->cam_list = elem;
		return ;
	}
	temp = s->cam_list;
	while (temp->next)
		temp = temp->next;
	temp->next = elem;
}

void	add_l_elem(t_scene_struct *s, t_l_struct *elem)
{
	t_l_struct *temp;

	if (!s->l_list)
	{
		s->l_list = elem;
		return ;
	}
	temp = s->l_list;
	while (temp->next)
		temp = temp->next;
	temp->next = elem;
}
	
void	print_elem(t_obj_struct *elem)
{
	if (!elem)
	{
		printf("\n***NULL elem***\n");
		return ;
	}
	printf("type: %c\n", elem->id);
	printf("xyz: %f,%f,%f\n", elem->xyz[X], elem->xyz[Y], elem->xyz[Z]);
	printf("normal: %f,%f,%f\n", elem->normal[X], elem->normal[Y], elem->normal[Z]);
	printf("colour ptr: %p\n", elem->colour);
	printf("colour: %d,%d,%d\n", elem->colour[X], elem->colour[Y], elem->colour[Z]);
	printf("data double: %f\n", elem->data.doubl);
	printf("tr: (%.2f,%.2f,%.2f)(%.2f,%.2f,%.2f)(%.2f,%.2f,%.2f)\n", elem->data.tr_points[0][0], elem->data.tr_points[0][1], elem->data.tr_points[0][2],
				 								   elem->data.tr_points[1][0], elem->data.tr_points[1][1], elem->data.tr_points[1][2],
				 								   elem->data.tr_points[2][0], elem->data.tr_points[2][1], elem->data.tr_points[2][2]);
	printf("data cy: d = %f, h = %f\n", elem->data.cy_d_h[0], elem->data.cy_d_h[1]);
	printf("norm function ptr: %p\n", elem->get_norm);
}

void	print_strs(char **strs)
{
	int i;

	i = 0;
	while (strs[i])
	{
		printf("%s\n", strs[i]);
		i++;
	}
}

int	simple_atoi(char *str)
{
	int output;

	if (!str || !(*str))
		return (-1);
	output = 0;
	while(*str > 47 && *str < 58)
	{
		output = (*str - 48) + (output * 10);
		str++;
	}
	if (!(*str))
		return (output);
	else
		return (-1);
}

double	tenths(char *str)
{
	int	i;
	int end_index;

	end_index = 0;
	while (str[end_index])
		end_index++;
	i = 0;
	while (str[i] != '.' && str[i])
		i++;
	if (str[i] == '.')
		return ((double)(pow(0.1, end_index - i - 1)));
	return (1);
}

int	ft_atof(char *str, double *fl)
{
	double	output;
	int		neg;
	char	*str_copy;

	str_copy = str;
	if (!str || !(*str))
		return (-1);
	output = 0;
	neg = 1;
	if (*str == '-' || *str == '+')
		neg = 44 - *str++;
	while((*str > 47 && *str < 58) || *str == '.')
	{
		if (*str != '.')
			output = (*str - 48) + (output * 10);
		str++;
	}
	if (*str)
		return (-1);
	*fl = output * neg * tenths(str_copy);
	return (0);
}

int	get_colour(char *str, int *colour)
{
	int		i;
	char	**strs;
	
	strs = ft_split(str, ',');
	if (len_str_arr(strs) != 3)
		return (-6);
	i = 0;
	while (i < 3)
	{
		if ((colour[i] = simple_atoi(strs[i])) == -1 || colour[i] > 255)
			return (-6);
		i++;
	}
	return (0);
}

int	get_data(char *str, double *data)
{
	if (ft_atof(str, data) == -1 || *data <= 0)
		return (-5);
	return (0);
}

int	get_xyz(char *str, double *xyz)
{
	int		i;
	char	**strs;

	strs = ft_split(str, ',');
	if (len_str_arr(strs) != 3)
		return (-3);
	i = 0;
	while (i < 3)
	{
		if (ft_atof(strs[i], xyz + i) == -1)
			return (-3);
		i++;
	}
	return (0);
}

int	len_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i])
		i++;
	return (i);
}

int	r_func(char *line, t_scene_struct *s)
{
	char	**strs;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 3)
		return (-1);
	s->res_xy[X] = simple_atoi(strs[1]);
	s->res_xy[Y] = simple_atoi(strs[2]);
	if (s->res_xy[X] < 1 || s->res_xy[Y] < 1)
		return (-5);
	if (s->res_xy[X] > RES_X)
		s->res_xy[X] = RES_X;
	if (s->res_xy[Y] > RES_Y)
		s->res_xy[Y] = RES_Y;
	return (0);
}

int	a_func(char *line, t_scene_struct *s)
{
	int		err_code;
	char	**strs;
	int		colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 3)
		return (-2);
	if ((err_code = get_data(strs[1], &(s->ambient_ratio))) < 0 ||
		(err_code = get_colour(strs[2], colour)) < 0)
		return (err_code);
	fill_ints(colour, s->ambient_colour, 3);
	return (0);
}

int	c_func(char *line, t_scene_struct *s)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i + 1] == ' ')
		return(cam_func(line, s));
	else if (line[i + 1] == 'y')
		return(cy_func(line, s));
	else
		return (-1);
}

int	l_func(char *line, t_scene_struct *s)
{
	int				err_code;
	char			**strs;
	double			xyz[3];
	double			brightness;
	int				colour[3];
	t_l_struct		*elem;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-2);
	if ((err_code = get_xyz(strs[1], xyz)) < 0 ||
		(err_code = get_data(strs[2], &brightness)) < 0 ||
		(err_code = get_colour(strs[3], colour)) < 0)
		return (err_code);
	if(!(elem = create_l_elem(xyz, brightness, colour)))
		return (-7);
	add_l_elem(s, elem);
	return (0);
}

int	s_func(char *line, t_scene_struct *s)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i + 1] == 'p')
		return(sp_func(line, s));
	else if (line[i + 1] == 'q')
		return(sq_func(line, s));
	else
		return (-1);
}

int	p_func(char *line, t_scene_struct *s)
{
	int				err_code;
	char			**strs;
	double			xyz[3];
	double			normal[3];
	int				colour[3];
	t_obj_struct	*elem;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4 || strs[0][1] != 'l')
		return (-2);
	if ((err_code = get_xyz(strs[1], xyz)) < 0 ||
		(err_code = get_xyz(strs[2], normal)) < 0 ||
		(err_code = get_colour(strs[3], colour)) < 0)
		return (err_code);
	if(!(elem = create_obj_elem('p', xyz, normal, colour)))
		return (-7);
	elem->get_norm = p_normal;
	elem->solve = plane_intercept;
	add_obj_elem(s, elem);
	return (0);
}

void	calc_tr_normal(t_obj_struct *tr)
{
	double	vec1[3];
	double	vec2[3];
	double	cross_prod[3];

	calc_3d_vector(tr->data.tr_points[0], tr->data.tr_points[1], vec1);
	calc_3d_vector(tr->data.tr_points[0], tr->data.tr_points[2], vec2);
	cross(vec1, vec2, cross_prod);
	fill_doubles(cross_prod, tr->normal, 3);
	calc_unit_vec(tr->normal, tr->normal);
}

int	t_func(char *line, t_scene_struct *s)
{
	int				err_code;
	char			**strs;
	double			points[3][3];
	int				colour[3];
	t_obj_struct	*elem;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 5 || strs[0][1] != 'r')
		return (-2);
	if ((err_code = get_xyz(strs[1], points[0])) < 0 ||
		(err_code = get_xyz(strs[2], points[1])) < 0 ||
		(err_code = get_xyz(strs[3], points[2])) < 0 ||
		(err_code = get_colour(strs[4], colour)) < 0)
		return (err_code);
	if(!(elem = create_obj_elem('t', NULL, NULL, colour)))
		return (-7);
	fill_doubles(points[0], elem->data.tr_points[0], 3);
	fill_doubles(points[1], elem->data.tr_points[1], 3);
	fill_doubles(points[2], elem->data.tr_points[2], 3);
	fill_doubles(points[0], elem->xyz, 3);
	calc_tr_normal(elem);
	elem->get_norm = tr_normal;
	elem->solve = tr_intercept;
	add_obj_elem(s, elem);
	return (0);
}

int	cam_func(char *line, t_scene_struct *s)
{
	int				err_code;
	char			**strs;
	double			xyz[3];
	double			normal[3];
	double			fov;
	t_cam_struct	*elem;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-2);
	if ((err_code = get_xyz(strs[1], xyz)) < 0 ||
		(err_code = get_xyz(strs[2], normal)) < 0 ||
		(err_code = get_data(strs[3], &fov)) < 0)
		return (err_code);
	if(!(elem = create_cam_elem(xyz, normal, fov)))
		return (-7);
	add_cam_elem(s, elem);
	return (0);
}
	
int	add_end_cap_objs(t_scene_struct *s, t_obj_struct *cy)
{
	t_obj_struct	*elem;
	double			proj_height;
	double			cam_to_centre[3];
	double			cap_1_xyz[3];
	double			cap_2_xyz[3];

	proj_height = sin(acos(dot(cy->normal, s->cam_list->normal)));
	proj_height *= (cy->data.cy_d_h[1] / 2);
	get_cy_end_point(cap_1_xyz, cy);
	cap_2_xyz[X] = cap_1_xyz[X] - (cy->data.cy_d_h[1] * cy->normal[X]);
	cap_2_xyz[Y] = cap_1_xyz[Y] - (cy->data.cy_d_h[1] * cy->normal[Y]);
	cap_2_xyz[Z] = cap_1_xyz[Z] - (cy->data.cy_d_h[1] * cy->normal[Z]);
	if(!(elem = create_obj_elem('i', cap_1_xyz, cy->normal, cy->colour)))
		return (0);
	elem->data.doubl = cy->data.cy_d_h[0];
	elem->get_norm = ci_normal;
	elem->solve = ci_intercept;
	add_obj_elem(s, elem);
	if(!(elem = create_obj_elem('i', cap_2_xyz, cy->normal, cy->colour)))
		return (0);
	elem->data.doubl = cy->data.cy_d_h[0];
	elem->get_norm = ci_normal;
	elem->solve = ci_intercept;
	add_obj_elem(s, elem);
	return (1);
}

int	cy_func(char *line, t_scene_struct *s)
{
	int				err_code;
	char			**strs;
	double			xyz[3];
	double			normal[3];
	double			diameter_height[2];
	int				colour[3];
	t_obj_struct	*elem;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 6)
		return (-2);
	if ((err_code = get_xyz(strs[1], xyz)) < 0 ||
		(err_code = get_xyz(strs[2], normal)) < 0 ||
		(err_code = get_colour(strs[3], colour)) < 0 ||
		(err_code = get_data(strs[4], diameter_height)) < 0 ||
		(err_code = get_data(strs[5], diameter_height + 1)) < 0)
		return (err_code);
	if(!(elem = create_obj_elem('c', xyz, normal, colour)))
		return (-7);
	/*should do this for all normals*/
	calc_unit_vec(elem->normal, elem->normal);
	fill_doubles(diameter_height, elem->data.cy_d_h, 2);
	elem->get_norm = cy_normal;
	elem->solve = cy_intercept;
	add_obj_elem(s, elem);
	if(!add_end_cap_objs(s, elem))
		return (-7);
	return (0);
}

int	sp_func(char *line, t_scene_struct *s)
{
	int				err_code;
	char			**strs;
	double			xyz[3];
	double			diameter;
	int				colour[3];
	t_obj_struct	*elem;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-2);
	if ((err_code = get_xyz(strs[1], xyz)) < 0 ||
		(err_code = get_data(strs[2], &diameter)) < 0 ||
		(err_code = get_colour(strs[3], colour)) < 0)
		return (err_code);
	if(!(elem = create_obj_elem('s', xyz, NULL, colour)))
		return (-7);
	elem->data.doubl = diameter;
	elem->get_norm = sp_normal;
	elem->solve = solve_quadratic;
	add_obj_elem(s, elem);
	return (0);
}

int	sq_func(char *line, t_scene_struct *s)
{
	int				err_code;
	int				colour[3];
	char			**strs;
	double			xyz[3];
	double			normal[3];
	double			side_size;
	t_obj_struct	*elem;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 5)
		return (-2);
	if ((err_code = get_xyz(strs[1], xyz)) < 0 ||
		(err_code = get_xyz(strs[2], normal)) < 0 ||
		(err_code = get_data(strs[3], &side_size)) < 0 ||
		(err_code = get_colour(strs[4], colour)) < 0)
		return (err_code);
	if(!(elem = create_obj_elem('q', xyz, normal, colour)))
		return (-7);
	elem->data.doubl = side_size;
	elem->get_norm = sq_normal;
	elem->solve = sq_intercept;
	add_obj_elem(s, elem);
	return (0);
}
