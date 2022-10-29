#include "minirt.h"

void	p_error(void)
{
	write(STDERR_FILENO, "Error: wrong number of arguments\n", 33);
	exit(EXIT_FAILURE);
}

void	msg_error(char *msg, char **line_split)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(1, "\n", 1);
	if (line_split != NULL)
		ft_split_del(&line_split);
	exit(EXIT_FAILURE);
}

void	m_error(void)
{
	write(STDERR_FILENO, mlx_strerror(mlx_errno),
		ft_strlen(mlx_strerror(mlx_errno)));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	error(void)
{
	write(STDERR_FILENO, "Error: allocation failed\n", 25);
	exit(EXIT_FAILURE);
}

void	leaks(void)
{
	system("leaks miniRT");
}
