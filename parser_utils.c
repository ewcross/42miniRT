/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:18:57 by ecross            #+#    #+#             */
/*   Updated: 2020/02/11 17:11:37 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

t_obj_struct	*create_elem(char id, double *xyz, double *normal, int *colour)
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

void	add_elem(t_scene_struct *s, t_obj_struct *elem)
{
	t_obj_struct *obj;

	if (!s->obj_list)
	{
		s->obj_list = elem;
		return ;
	}
	obj = s->obj_list;
	while (obj->next)
		obj = obj->next;
	obj->next = elem;
}
	
void	print_elem(t_obj_struct *elem)
{
	printf("type: %c\n", elem->id);
	printf("xyz: %f,%f,%f\n", elem->xyz[X], elem->xyz[Y], elem->xyz[Z]);
	printf("normal: %f,%f,%f\n", elem->normal[X], elem->normal[Y], elem->normal[Z]);
	printf("colour ptr: %p\n", elem->colour);
	printf("colour: %d,%d,%d\n", elem->colour[X], elem->colour[Y], elem->colour[Z]);
	printf("data double: %f\n", elem->data.doubl);
	printf("tr: (%.2f,%.2f,%.2f)(%.2f,%.2f,%.2f)(%.2f,%.2f,%.2f)\n", elem->data.tr_points[0][0], elem->data.tr_points[0][1], elem->data.tr_points[0][2],
				 								   elem->data.tr_points[1][0], elem->data.tr_points[1][1], elem->data.tr_points[1][2],
				 								   elem->data.tr_points[2][0], elem->data.tr_points[2][1], elem->data.tr_points[2][2]);
	printf("data cy: d = %f, h = %f\n", elem->data.cy_diam_height[0], elem->data.cy_diam_height[1]);
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
		return (-1);
	i = 0;
	while (i < 3)
	{
		if ((colour[i] = simple_atoi(strs[i])) == -1 || colour[i] > 255)
			return (-1);
		i++;
	}
	return (0);
}

int	get_xyz(char *str, double *xyz)
{
	int		i;
	char	**strs;

	strs = ft_split(str, ',');
	if (len_str_arr(strs) != 3)
		return (-1);
	i = 0;
	while (i < 3)
	{
		if (ft_atof(strs[i], xyz + i) == -1)
			return (-1);
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
		return (-1);
	return (0);
}

int	a_func(char *line, t_scene_struct *s)
{
	char	**strs;
	double	ratio;
	int		colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 3)
		return (-1);
	if (ft_atof(strs[1], &(s->ambient_ratio)) == -1 || ratio < 0)
		return (-1);
	if (get_colour(strs[2], colour) == -1)
		return (-1);
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
	char			**strs;
	double			xyz[3];
	double			brightness;
	int				colour[3];
	t_obj_struct	*elem;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-1);
	if (get_xyz(strs[1], xyz) == -1)
		return (-1);
	if (ft_atof(strs[2], &brightness) == -1 || brightness < 0)
		return (-1);
	if (get_colour(strs[3], colour) == -1)
		return (-1);
	if(!(elem = create_elem('l', xyz, NULL, colour)))
		return (-2);
	elem->data.doubl = brightness;
	add_elem(s, elem);
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
	char			**strs;
	double			xyz[3];
	double			normal[3];
	int				colour[3];
	t_obj_struct	*elem;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4 || strs[0][1] != 'l')
		return (-1);
	if (get_xyz(strs[1], xyz) == -1)
		return (-1);
	if (get_xyz(strs[2], normal) == -1)
		return (-1);
	if (get_colour(strs[3], colour) == -1)
		return (-1);
	if(!(elem = create_elem('p', xyz, normal, colour)))
		return (-2);
	add_elem(s, elem);
	return (0);
}

int	t_func(char *line, t_scene_struct *s)
{
	char			**strs;
	double			points[3][3];
	int				colour[3];
	t_obj_struct	*elem;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 5 || strs[0][1] != 'r')
		return (-1);
	if (get_xyz(strs[1], points[0]) == -1)
		return (-1);
	if (get_xyz(strs[2], points[1]) == -1)
		return (-1);
	if (get_xyz(strs[3], points[2]) == -1)
		return (-1);
	if (get_colour(strs[4], colour) == -1)
		return (-1);
	if(!(elem = create_elem('t', NULL, NULL, colour)))
		return (-2);
	fill_doubles(points[0], elem->data.tr_points[0], 3);
	fill_doubles(points[1], elem->data.tr_points[1], 3);
	fill_doubles(points[2], elem->data.tr_points[2], 3);
	add_elem(s, elem);
	return (0);
}

int	cam_func(char *line, t_scene_struct *s)
{
	char			**strs;
	double			xyz[3];
	double			normal[3];
	double			fov;
	t_obj_struct	*elem;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-1);
	if (get_xyz(strs[1], xyz) == -1)
		return (-1);
	if (get_xyz(strs[2], normal) == -1)
		return (-1);
	if (ft_atof(strs[3], &fov) == -1 || fov < 0)
		return (-1);
	if(!(elem = create_elem('C', xyz, normal, NULL)))
		return (-2);
	elem->data.doubl = fov;
	add_elem(s, elem);
	return (0);
}

int	cy_func(char *line, t_scene_struct *s)
{
	char			**strs;
	double			xyz[3];
	double			normal[3];
	double			diameter_height[2];
	int				colour[3];
	t_obj_struct	*elem;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 6)
		return (-1);
	if (get_xyz(strs[1], xyz) == -1)
		return (-1);
	if (get_xyz(strs[2], normal) == -1)
		return (-1);
	if (get_colour(strs[3], colour) == -1)
		return (-1);
	if (ft_atof(strs[4], diameter_height) == -1 || diameter_height[0] < 0)
		return (-1);
	if (ft_atof(strs[5], diameter_height + 1) == -1 || diameter_height[1] < 0)
		return (-1);
	if(!(elem = create_elem('c', xyz, normal, colour)))
		return (-2);
	fill_doubles(diameter_height, elem->data.cy_diam_height, 2);
	add_elem(s, elem);
	return (0);
}

int	sp_func(char *line, t_scene_struct *s)
{
	char			**strs;
	double			xyz[3];
	double			diameter;
	int				colour[3];
	t_obj_struct	*elem;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-1);
	if (get_xyz(strs[1], xyz) == -1)
		return (-1);
	if (ft_atof(strs[2], &diameter) == -1 || diameter < 0)
		return (-1);
	if (get_colour(strs[3], colour) == -1)
		return (-1);
	if(!(elem = create_elem('S', xyz, NULL, colour)))
		return (-2);
	elem->data.doubl = diameter;
	add_elem(s, elem);
	return (0);
}

int	sq_func(char *line, t_scene_struct *s)
{
	char	**strs;
	double	square_xyz[3];
	double	normal_xyz[3];
	double	side_size;
	int		square_colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 5)
		return (-1);
	if (get_xyz(strs[1], square_xyz) == -1)
		return (-1);
	if (get_xyz(strs[2], normal_xyz) == -1)
		return (-1);
	if (ft_atof(strs[3], &side_size) == -1 || side_size < 0)
		return (-1);
	if (get_colour(strs[4], square_colour) == -1)
		return (-1);
	return (0);
}
