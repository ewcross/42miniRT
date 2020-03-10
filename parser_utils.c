/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:18:57 by ecross            #+#    #+#             */
/*   Updated: 2020/03/10 09:19:20 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "structs.h"

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

t_obj_struct	*create_obj_elem(double *xyz, double *normal, int *colour)
{
	t_obj_struct *elem;

	if(!(elem = (t_obj_struct*)malloc(sizeof(t_obj_struct))))
		return (NULL);
	elem->inside = 0;
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
	free_strs(strs);
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
	free_strs(strs);
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

int	create_add_cam(t_scene_struct *s, double *xyz, double *normal, double fov)
{
	t_cam_struct *elem;

	if(!(elem = create_cam_elem(xyz, normal, fov)))
		return (0);
	add_cam_elem(s, elem);
	return (1);
}
	
int	create_add_l(t_scene_struct *s, double *xyz, double bright, int *colour)
{
	t_l_struct	*elem;

	if(!(elem = create_l_elem(xyz, bright, colour)))
		return (0);
	add_l_elem(s, elem);
	return (1);
}

int	create_add_obj(t_scene_struct *s, double *xyz, double *normal, int *colour)
{
	t_obj_struct *elem;

	if(!(elem = create_obj_elem(xyz, normal, colour)))
		return (0);
	add_obj_elem(s, elem);
	return (1);
}

int	r_func(char *line, t_scene_struct *s)
{
	char	**strs;

	if (s->res_xy[X] && s->res_xy[Y])
		return (-8);
	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 3)
		return (-1);
	s->res_xy[X] = simple_atoi(strs[1]);
	s->res_xy[Y] = simple_atoi(strs[2]);
	if (s->res_xy[X] < 1 || s->res_xy[Y] < 1)
		return (-5);
	if (s->res_xy[X] > MAX_RES_X)
		s->res_xy[X] = MAX_RES_X;
	if (s->res_xy[Y] > MAX_RES_Y)
		s->res_xy[Y] = MAX_RES_Y;
	free_strs(strs);
	return (0);
}

int	a_func(char *line, t_scene_struct *s)
{
	int		err_code;
	char	**strs;
	int		colour[3];

	if (s->ambient_ratio != -1)
		return (-8);
	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 3)
		return (-2);
	if (((err_code = get_data(strs[1], &(s->ambient_ratio))) < 0 &&
			s->ambient_ratio < 0) ||
		(err_code = get_colour(strs[2], colour)) < 0)
		return (err_code);
	fill_ints(colour, s->ambient_colour, 3);
	free_strs(strs);
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

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-2);
	if ((err_code = get_xyz(strs[1], xyz)) < 0 ||
		(err_code = get_data(strs[2], &brightness)) < 0 ||
		(err_code = get_colour(strs[3], colour)) < 0)
		return (err_code);
	if (!create_add_l(s, xyz, brightness, colour))
		return (-7);
	free_strs(strs);
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

int	check_normal(double *normal)
{
	if (normal[X] == 0 && normal[Y] == 0 && normal[Z] == 0)
		return (-4);
	calc_unit_vec(normal, normal);
	return (0);
}

void	add_p_data(t_scene_struct *s)
{
	t_obj_struct *obj;

	obj = s->obj_list;
	while (obj->next)
		obj = obj->next;
	obj->id = 'p';
	obj->get_norm = p_normal;
	obj->solve = plane_intercept;
}

int	p_func(char *line, t_scene_struct *s)
{
	int				err_code;
	char			**strs;
	double			xyz[3];
	double			normal[3];
	int				colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4 || strs[0][1] != 'l')
		return (-2);
	if ((err_code = get_xyz(strs[1], xyz)) < 0 ||
		(err_code = get_xyz(strs[2], normal)) < 0 ||
		(err_code = check_normal(normal)) < 0 ||
		(err_code = get_colour(strs[3], colour)) < 0)
		return (err_code);
	if (!create_add_obj(s, xyz, normal, colour))
		return (-7);
	add_p_data(s);
	free_strs(strs);
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

void	add_tr_data(t_scene_struct *s, double points[3][3])
{
	t_obj_struct *obj;

	obj = s->obj_list;
	while (obj->next)
		obj = obj->next;
	obj->id = 't';
	fill_doubles(points[0], obj->data.tr_points[0], 3);
	fill_doubles(points[1], obj->data.tr_points[1], 3);
	fill_doubles(points[2], obj->data.tr_points[2], 3);
	fill_doubles(points[0], obj->xyz, 3);
	calc_tr_normal(obj);
	obj->get_norm = tr_normal;
	obj->solve = tr_intercept;
}

int	t_func(char *line, t_scene_struct *s)
{
	int				err_code;
	char			**strs;
	double			points[3][3];
	int				colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 5 || strs[0][1] != 'r')
		return (-2);
	if ((err_code = get_xyz(strs[1], points[0])) < 0 ||
		(err_code = get_xyz(strs[2], points[1])) < 0 ||
		(err_code = get_xyz(strs[3], points[2])) < 0 ||
		(err_code = get_colour(strs[4], colour)) < 0)
		return (err_code);
	if (!create_add_obj(s, NULL, NULL, colour))
		return (-7);
	add_tr_data(s, points);
	free_strs(strs);
	return (0);
}

void	get_rotation_data(t_cam_struct *cam)
{
	double			dot_prod;
	static double	z_axis[] = {0, 0, 1};

	dot_prod = dot(cam->normal, z_axis);
	cam->rot_angle = acos(dot_prod);
	if (dot_prod == 1)
		return ;
	if (dot_prod == -1)
	{
		cam->rot_axis[X] = 0;
		cam->rot_axis[Y] = 1;
		cam->rot_axis[Z] = 0;
		return ;
	}
	cross(cam->normal, z_axis, cam->rot_axis);
	calc_unit_vec(cam->rot_axis, cam->rot_axis);
	scale_vector(cam->rot_axis, -1, cam->rot_axis);
}

void	add_cam_data(t_scene_struct *s)
{
	t_cam_struct *cam;

	cam = s->cam_list;
	while (cam->next)
		cam = cam->next;
	get_rotation_data(cam);
}

int	cam_func(char *line, t_scene_struct *s)
{
	int				err_code;
	char			**strs;
	double			xyz[3];
	double			normal[3];
	double			fov;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-2);
	if ((err_code = get_xyz(strs[1], xyz)) < 0 ||
		(err_code = get_xyz(strs[2], normal)) < 0 ||
		(err_code = check_normal(normal)) < 0 ||
		(err_code = get_data(strs[3], &fov)) < 0)
		return (err_code);
	if (!create_add_cam(s, xyz, normal, fov))
		return (-7);
	add_cam_data(s);
	free_strs(strs);
	return (0);
}
	
void	add_cy_data(t_scene_struct *s, double *diameter_height)
{
	t_obj_struct *obj;

	obj = s->obj_list;
	while (obj->next)
		obj = obj->next;
	obj->id = 'c';
	fill_doubles(diameter_height, obj->data.cy_d_h, 2);
	obj->get_norm = cy_normal;
	obj->solve = cy_intercept;
}

int	cy_func(char *line, t_scene_struct *s)
{
	int				err_code;
	char			**strs;
	double			xyz_norm[6];
	double			diameter_height[2];
	int				colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 6)
		return (-2);
	if ((err_code = get_xyz(strs[1], xyz_norm)) < 0 ||
		(err_code = get_xyz(strs[2], xyz_norm + 3)) < 0 ||
		(err_code = check_normal(xyz_norm + 3)) < 0 ||
		(err_code = get_colour(strs[3], colour)) < 0 ||
		(err_code = get_data(strs[4], diameter_height)) < 0 ||
		(err_code = get_data(strs[5], diameter_height + 1)) < 0)
		return (err_code);
	if (!create_add_obj(s, xyz_norm, xyz_norm + 3, colour))
		return (-7);
	add_cy_data(s, diameter_height);
	free_strs(strs);
	return (0);
}

void	add_sp_data(t_scene_struct *s, double diameter)
{
	t_obj_struct *obj;

	obj = s->obj_list;
	while (obj->next)
		obj = obj->next;
	obj->id = 's';
	obj->data.doubl = diameter;
	obj->get_norm = sp_normal;
	obj->solve = solve_quadratic;
}

int	sp_func(char *line, t_scene_struct *s)
{
	int				err_code;
	char			**strs;
	double			xyz[3];
	double			diameter;
	int				colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-2);
	if ((err_code = get_xyz(strs[1], xyz)) < 0 ||
		(err_code = get_data(strs[2], &diameter)) < 0 ||
		(err_code = get_colour(strs[3], colour)) < 0)
		return (err_code);
	if (!create_add_obj(s, xyz, NULL, colour))
		return (-7);
	add_sp_data(s, diameter);
	free_strs(strs);
	return (0);
}

void	add_sq_data(t_scene_struct *s, double side_size)
{
	t_obj_struct *obj;

	obj = s->obj_list;
	while (obj->next)
		obj = obj->next;
	obj->id = 'q';
	obj->data.doubl = side_size;
	obj->get_norm = sq_normal;
	obj->solve = sq_intercept;
}

int	sq_func(char *line, t_scene_struct *s)
{
	int				err_code;
	int				colour[3];
	char			**strs;
	double			xyz_norm[6];
	double			side_size;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 5)
		return (-2);
	if ((err_code = get_xyz(strs[1], xyz_norm)) < 0 ||
		(err_code = get_xyz(strs[2], xyz_norm + 3)) < 0 ||
		(err_code = check_normal(xyz_norm + 3)) < 0 ||
		(err_code = get_data(strs[3], &side_size)) < 0 ||
		(err_code = get_colour(strs[4], colour)) < 0)
		return (err_code);
	if (!create_add_obj(s, xyz_norm, xyz_norm + 3, colour))
		return (-7);
	add_sq_data(s, side_size);
	free_strs(strs);
	return (0);
}
