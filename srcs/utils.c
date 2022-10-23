#include "minirt.h"

bool	ft_bit_range(t_color color)
{
	if (color.r < 0 || color.r > 255)
		return (false);
	else if (color.g < 0 || color.g > 255)
		return (false);
	else if (color.b < 0 || color.b > 255)
		return (false);
	else
		return (true);
}

//this should also look for normalized??
bool	ft_unit_range(t_vector vec)
{
	if (ft_f_less_f(vec.x, -1.0) || ft_f_greater_f(vec.x, 1.0))
		return (false);
	else if (ft_f_less_f(vec.y, -1.0) || ft_f_greater_f(vec.y, 1.0))
		return (false);
	else if (ft_f_less_f(vec.z, -1.0) || ft_f_greater_f(vec.z, 1.0))
		return (false);
	else if (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z != 1)
		normalize_vec(&vec);
	return (true);
}

t_color	parse_color(char **line_split, int i)
{
	t_color	color;
	char	**split_colors;

	split_colors = ft_split(line_split[i], ',');
	if (!split_colors[0] || !split_colors[1]
		|| !split_colors[2] || split_colors[3])
	{
		ft_split_del(&split_colors);
		msg_error("Not the right color input", line_split);
	}
	color.r = ft_atoi(split_colors[0]);
	color.g = ft_atoi(split_colors[1]);
	color.b = ft_atoi(split_colors[2]);
	ft_split_del(&split_colors);
	return (color);
}

t_vector	split_coordinates(char **str, int i)
{
	char		**split_coord;
	t_vector	coordinates;

	split_coord = ft_split(str[i], ',');
	if (!split_coord[0] || !split_coord[1] || !split_coord[2] || split_coord[3])
		msg_error("Wrong coordinates input", str);
	coordinates.x = ft_stof(split_coord[0]);
	coordinates.y = ft_stof(split_coord[1]);
	coordinates.z = ft_stof(split_coord[2]);
	ft_split_del(&split_coord);
	return (coordinates);
}
