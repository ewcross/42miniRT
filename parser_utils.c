/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:18:57 by ecross            #+#    #+#             */
/*   Updated: 2020/02/04 12:54:00 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

int	ft_atof(char *str, float *fl)
{
	/*function convert string to float
	  and store it in address provided
	  returns -1 on error or 0 on success*/
	printf("float here\n");
	return (0);
}

int	get_colour(char *str, int *colour)
{
	/*convert string to colour - split by
	  commas, then atoi on each section and
	  store result in colour[0], [1] and [2]
	  return -1 on error and 0 on success*/
	printf("colour here\n");
	return (0);
}

int	get_xyz(char *str, float *coords)
{
	/*convert string to coordinates - split by
	  commas, then atof on each section and
	  store result in coords[0], [1] and [2]
	  return -1 on error and 0 on success*/
	printf("coords here\n");
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

/********************************/

int	R_func(char *line)
{
	int		res_x;
	int		res_y;
	char	**strs;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 3)
		return (-1);
	res_x = simple_atoi(strs[1]);
	res_y = simple_atoi(strs[2]);
	if (res_x < 1 || res_y < 1)
		return (-1);
	return (0);
}

int	A_func(char *line)
{
	char	**strs;
	float	ratio;
	int		colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 3)
		return (-1);
	if (ft_atof(strs[1], &ratio) == -1)
		return (-1);
	if (get_colour(strs[2], colour) == -1)
		return (-1);
	return (0);
}

int	c_func(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i + 1] == ' ')
		return(cam_func(line));
	else if (line[i + 1] == 'y')
		return(cy_func(line));
	else
		return (-1);
}

int	l_func(char *line)
{
	char	**strs;
	float	light_xyz[3];
	float	brightness;
	int		colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-1);
	if (get_xyz(strs[1], light_xyz) == -1)
		return (-1);
	if (ft_atof(strs[2], &brightness) == -1)
		return (-1);
	if (get_colour(strs[3], colour) == -1)
		return (-1);
	return (0);
}

int	s_func(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i + 1] == 'p')
		return(sp_func(line));
	else if (line[i + 1] == 'q')
		return(sq_func(line));
	else
		return (-1);
}

int	p_func(char *line)
{
	char	**strs;
	float	plane_xyz[3];
	float	normal_xyz[3];
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

int	t_func(char *line)
{
	char	**strs;
	float	points_xyz[3][3];
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

int	cam_func(char *line)
{
	char	**strs;
	float	cam_xyz[3];
	float	cam_norm[3];
	int		cam_fov;

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-1);
	if (get_xyz(strs[1], cam_xyz) == -1)
		return (-1);
	if (get_xyz(strs[2], cam_norm) == -1)
		return (-1);
	if (simple_atoi(strs[3]) < 1)
		return (-1);
	return (0);
}

int	cy_func(char *line)
{
	char	**strs;
	float	cylinder_xyz[3];
	float	normal_xyz[3];
	float	diameter;
	float	height;
	int		cylinder_colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 6)
		return (-1);
	if (get_xyz(strs[1], cylinder_xyz) == -1)
		return (-1);
	if (get_xyz(strs[2], normal_xyz) == -1)
		return (-1);
	if (ft_atof(strs[3], &diameter) == -1)
		return (-1);
	if (ft_atof(strs[4], &height) == -1)
		return (-1);
	if (get_colour(strs[5], cylinder_colour) == -1)
		return (-1);
	return (0);
}

int	sp_func(char *line)
{
	char	**strs;
	float	sphere_xyz[3];
	float	diameter;
	int		sphere_colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 4)
		return (-1);
	if (get_xyz(strs[1], sphere_xyz) == -1)
		return (-1);
	if (ft_atof(strs[2], &diameter) == -1)
		return (-1);
	if (get_colour(strs[3], sphere_colour) == -1)
		return (-1);
	return (0);
}

int	sq_func(char *line)
{
	char	**strs;
	float	square_xyz[3];
	float	normal_xyz[3];
	float	side_size;
	int		square_colour[3];

	strs = ft_split(line, ' ');
	if (len_str_arr(strs) != 5)
		return (-1);
	if (get_xyz(strs[1], square_xyz) == -1)
		return (-1);
	if (get_xyz(strs[2], normal_xyz) == -1)
		return (-1);
	if (ft_atof(strs[3], &side_size) == -1)
		return (-1);
	if (get_colour(strs[4], square_colour) == -1)
		return (-1);
	return (0);
}
