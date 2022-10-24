#include "minirt.h"

static t_minirt	*in_scene(t_minirt *mt, char **split_line)
{
	if (ft_strncmp(split_line[0], "A", 2) == 0)
		mt->scene = parse_ambi_light(mt->scene, split_line);
	else if (ft_strncmp(split_line[0], "C", 2) == 0)
		mt->scene = parse_camera(mt->scene, split_line);
	else if (ft_strncmp(split_line[0], "L", 2) == 0)
		mt->scene = parse_light(mt->scene, split_line);
	else if (ft_strncmp(split_line[0], "sp", 3) == 0)
		mt->obj = parse_sphere(mt->obj, split_line);
	else if (ft_strncmp(split_line[0], "pl", 3) == 0)
		mt->obj = parse_plane(mt->obj, split_line);
	else if (ft_strncmp(split_line[0], "cy", 3) == 0)
		mt->obj = parse_cylinder(mt->obj, split_line);
	else if (ft_strncmp(split_line[0], "\n", 1) == 0 || split_line[0][0] == '#')
		split_line[0][0] = '\n';
	else
		msg_error(split_line[0], split_line);
	ft_split_del(&split_line);
	return (mt);
}

char	*ft_whitespace(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\t' || line[i] == '\v' || line[i] == '\f')
			line[i] = ' ';
		i++;
	}
	return (line);
}

static t_minirt	*readfile(t_minirt *mt, int fd)
{
	char	*line;
	char	*tmp;
	char	**split_line;
	int		i;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line = ft_whitespace(line);
		split_line = ft_split(line, ' ');
		i = 0;
		while (split_line[i] != NULL)
		{
			tmp = ft_strtrim(split_line[i], "\t ");
			split_line[i] = tmp;
			i++;
		}
		ft_free(line);
		mt = in_scene(mt, split_line);
	}
	return (mt);
}

void	parser(t_minirt *mt, char *argv)
{
	int		fd;
	char	*src;

	src = ft_strjoin("./scenes/", argv);
	fd = open(src, O_RDONLY);
	ft_free(src);
	if (fd < 0)
		p_error();
	mt = readfile(mt, fd);
	if (mt->scene.camera.fov == -1
		|| ft_comp_float(mt->scene.a_light.ratio, -1.0) == 0
		|| ft_comp_float(mt->scene.light.bright, -1.0) == 0)
		p_error();
	close(fd);
}
