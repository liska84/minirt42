#include "minirt.h"
// File descriptor leaks?????
void	free_content(void *content)
{
	free(content);
}

t_obj parse_sphere(t_obj object, char **line_split)
{
	t_sphere	*sphere;
	t_list		*new;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
	{
		ft_split_del(&line_split);
		p_error();
	}
	if (line_split[4] && ft_strncmp(line_split[4], "\n", 1) == 0);
	else if (!line_split[3] || line_split[4])
		msg_error("Not the right sp input", line_split);
	sphere->center = split_coordinates(line_split, 1);
	sphere->diam = ft_stof(line_split[2]);
	sphere->color = parse_color(line_split, 3);
	if (!ft_bit_range(sphere->color))
		msg_error("'sp': colors out of range", line_split);
	new = ft_lstnew(sphere);
	if (!new)
		msg_error("Error\n", line_split);
	ft_lstadd_back(&object.sphere, new);
	return(object);
}

t_obj parse_plane(t_obj obj, char **line_split)
{
	t_plane *plane;
	t_list	*new;

	plane = malloc(sizeof(t_plane));
	if (!plane)
	{
		ft_split_del(&line_split);
		p_error();
	}
	if (line_split[4] && ft_strncmp(line_split[4], "\n", 1) == 0);
	else if (!line_split[3] || line_split[4])
		msg_error("Not the right pl input", line_split);
	plane->coord = split_coordinates(line_split, 1);
	plane->orientation = split_coordinates(line_split, 2);
	if (!ft_unit_range(plane->orientation))
		msg_error("'pl': orientaion out of range", line_split);
	plane->color = parse_color(line_split, 3);
	if (!ft_bit_range(plane->color))
		msg_error("'pl': colors out of range", line_split);
	new = ft_lstnew(plane);
	if(!new)
		msg_error("Error\n", line_split);
	ft_lstadd_back(&obj.plane, new);
	return(obj);
}

t_obj parse_cylinder(t_obj obj, char **line_split)
{
	t_cylinder 	*cylinder;
	t_list 		*new;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
	{
		ft_split_del(&line_split);
		p_error();
	}
	if (line_split[6] && ft_strncmp(line_split[6], "\n", 1) == 0);
	else if (!line_split[5] || line_split[6])
		msg_error("Not the right cy input", line_split);
	cylinder->coordinates = split_coordinates(line_split, 1);
	cylinder->orientation = split_coordinates(line_split, 2);
	if (!ft_unit_range(cylinder->orientation))
		msg_error("'cy': orientaion out of range", line_split);
	cylinder->diameter = ft_stof(line_split[3]);
	cylinder->height = ft_stof(line_split[4]);
	cylinder->color = parse_color(line_split, 5);
	if (!ft_bit_range(cylinder->color))
		msg_error("'cy': colors out of range", line_split);
	new = ft_lstnew(cylinder);
	if(!new)
		msg_error("Error\n", line_split);
	ft_lstadd_back(&obj.cylinder, new);
	return(obj);
}
