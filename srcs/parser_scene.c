#include "minirt.h"

t_scene parse_ambi_light(t_scene scene, char **line_split)
{
	if (scene.a_light.ratio != -1.0)
		msg_error("A was declared more than once", line_split);
	if (line_split[3] && ft_strncmp(line_split[3], "\n", 1) == 0);
	else if (!line_split[1] || !line_split[2] || line_split[3])
		msg_error("Not the right 'A' input", line_split);
	scene.a_light.ratio = ft_stof(line_split[1]);
	if (ft_f_less_f(scene.a_light.ratio, 0.0) || ft_f_greater_f(scene.a_light.ratio, 1.0))
		msg_error("'A': light_ratio out of range", line_split);
	scene.a_light.color = parse_color(line_split, 2);
	if (!ft_bit_range(scene.a_light.color))
		msg_error("'A': colors out of range", line_split);
	return (scene);
}

t_scene parse_camera(t_scene scene, char **line_split)
{
	if (scene.camera.fov != -1)
		msg_error("C was declared more than once", line_split);
	if (line_split[4] && ft_strncmp(line_split[4], "\n", 1) == 0);
	else if (!line_split[3] || line_split[4])
		msg_error("Not the right 'C' input", line_split);
	scene.camera.origin = split_coordinates(line_split, 1);
	scene.camera.direction = split_coordinates(line_split, 2);
	if (!ft_unit_range(scene.camera.direction))
		msg_error("'C': orientaion out of range", line_split);
	scene.camera.fov = ft_atoi(line_split[3]);
	if (!ft_string_digit(line_split[3]) || scene.camera.fov < 0 || scene.camera.fov > 180)
		msg_error("'C': fov out of range", line_split);
	return (scene);
}

t_scene parse_light(t_scene scene, char **line_split)
{
	if (ft_compare_float(-1, scene.light.bright) == 0)
		msg_error("L was declared more than once", line_split);
	if (line_split[4] && ft_strncmp(line_split[4], "\n", 1) == 0);
	else if (!line_split[3] || line_split[4])
		msg_error("Not the right L input", line_split);
	scene.light.coord = split_coordinates(line_split, 1);
	scene.light.bright =  ft_stof(line_split[2]);
	if (ft_f_less_f(scene.light.bright, 0.0) || ft_f_greater_f(scene.light.bright, 1.0))
		msg_error("'L': brightness out of range", line_split);
	scene.light.color = parse_color(line_split, 3);
	if (!ft_bit_range(scene.light.color))
		msg_error("'L': colors out of range", line_split);
	return (scene);
}
