/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:18:57 by ecross            #+#    #+#             */
/*   Updated: 2020/02/11 11:50:37 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
	print_strs(strs);
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
	print_strs(strs);
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
	if (ft_atof(strs[1], &ratio) == -1 || ratio < 0)
		return (-1);
	if (get_colour(strs[2], colour) == -1)
		return (-1);
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
	char	**strs;
	double	light_xyz[3];
	double	brightness;
	int		colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-1);
	if (get_xyz(strs[1], light_xyz) == -1)
		return (-1);
	if (ft_atof(strs[2], &brightness) == -1 || brightness < 0)
		return (-1);
	if (get_colour(strs[3], colour) == -1)
		return (-1);
	printf("%f, %f, %f\n", light_xyz[X], light_xyz[Y], light_xyz[Z]);
	printf("%d, %d, %d\n", colour[R], colour[G], colour[B]);
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
	char	**strs;
	double	plane_xyz[3];
	double	normal_xyz[3];
	int		plane_colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4 || strs[0][1] != 'l')
		return (-1);
	if (get_xyz(strs[1], plane_xyz) == -1)
		return (-1);
	if (get_xyz(strs[2], normal_xyz) == -1)
		return (-1);
	if (get_colour(strs[3], plane_colour) == -1)
		return (-1);
	return (0);
}

int	t_func(char *line, t_scene_struct *s)
{
	char	**strs;
	double	points_xyz[3][3];
	int		triangle_colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 5 || strs[0][1] != 'r')
		return (-1);
	if (get_xyz(strs[1], points_xyz[0]) == -1)
		return (-1);
	if (get_xyz(strs[2], points_xyz[1]) == -1)
		return (-1);
	if (get_xyz(strs[3], points_xyz[2]) == -1)
		return (-1);
	if (get_colour(strs[4], triangle_colour) == -1)
		return (-1);
	return (0);
}

int	cam_func(char *line, t_scene_struct *s)
{
	char	**strs;
	double	cam_xyz[3];
	double	cam_norm[3];
	double	cam_fov;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-1);
	if (get_xyz(strs[1], cam_xyz) == -1)
		return (-1);
	if (get_xyz(strs[2], cam_norm) == -1)
		return (-1);
	if (ft_atof(strs[3], &cam_fov) == -1 || cam_fov < 0)
		return (-1);
	/*add to cam chain and store*/
	return (0);
}

int	cy_func(char *line, t_scene_struct *s)
{
	char	**strs;
	double	cylinder_xyz[3];
	double	normal_xyz[3];
	double	diameter;
	double	height;
	int		cylinder_colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 6)
		return (-1);
	if (get_xyz(strs[1], cylinder_xyz) == -1)
		return (-1);
	if (get_xyz(strs[2], normal_xyz) == -1)
		return (-1);
	if (ft_atof(strs[3], &diameter) == -1 || diameter < 0)
		return (-1);
	if (ft_atof(strs[4], &height) == -1 || height < 0)
		return (-1);
	if (get_colour(strs[5], cylinder_colour) == -1)
		return (-1);
	printf("cyl pos:\n\n(%f,%f,%f)\n\n", cylinder_xyz[X], cylinder_xyz[Y], cylinder_xyz[Z]);
	printf("cyl norm:\n\n(%f,%f,%f)\n\n", normal_xyz[X], normal_xyz[Y], normal_xyz[Z]);
	printf("cyl diameter:\n\n%f\n\n", diameter);
	printf("cyl height:\n\n%f\n\n", height);
	printf("cyl colour:\n\n(%d, %d, %d)\n\n", cylinder_colour[R], cylinder_colour[G], cylinder_colour[B]);
	return (0);
}

int	sp_func(char *line, t_scene_struct *s)
{
	char	**strs;
	double	sphere_xyz[3];
	double	diameter;
	int		sphere_colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-1);
	if (get_xyz(strs[1], sphere_xyz) == -1)
		return (-1);
	if (ft_atof(strs[2], &diameter) == -1 || diameter < 0)
		return (-1);
	if (get_colour(strs[3], sphere_colour) == -1)
		return (-1);
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
