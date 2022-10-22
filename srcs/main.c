#include "minirt.h"

void free_list(t_list *head)
{
   t_list* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

void leaks()
{
	system("leaks minirt");
}

void error(void)
{
	write(STDERR_FILENO, "Error: allocation failed\n", 25);
	exit(EXIT_FAILURE);
}

void p_error(void)
{
	write(STDERR_FILENO, "Error: wrong number of arguments\n", 33);
	exit(EXIT_FAILURE);
}

void msg_error(char *msg, char **line_split)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(1, "\n", 1);
	if (line_split != NULL)
		ft_split_del(&line_split);
	exit(EXIT_FAILURE);
}

void m_error(void)
{
	write(STDERR_FILENO, mlx_strerror(mlx_errno), ft_strlen(mlx_strerror(mlx_errno)));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	init_mt(t_minirt *mt)
{
	mt->scene.a_light.ratio = -1.0;
	mt->scene.a_light.color.r = 0;
	mt->scene.a_light.color.g = 0;
	mt->scene.a_light.color.b = 0;
	mt->scene.camera.origin.x = 0.0;
	mt->scene.camera.origin.y = 0.0;
	mt->scene.camera.origin.z = 0.0;
	mt->scene.camera.direction.x = 0.0;
	mt->scene.camera.direction.y = 0.0;
	mt->scene.camera.direction.z = 0.0;
	mt->scene.camera.fov = -1;
	mt->scene.light.bright = -1.0;
	mt->scene.light.coord.x = 0.0;
	mt->scene.light.coord.y = 0.0;
	mt->scene.light.coord.z = 0.0;
	mt->scene.light.color.r = 0.0;
	mt->scene.light.color.g = 0.0;
	mt->scene.light.color.b = 0.0;
	mt->obj.sphere = NULL;
	mt->obj.plane = NULL;
	mt->obj.cylinder = NULL;
	mt->gr.mlx = NULL;
	mt->gr.img = NULL;
}

int main(int ac, char **av) 
{
	(void)av;
	t_minirt	*mt;

	atexit(leaks);
	mt = malloc(sizeof(t_minirt));
	mt->width = 1920;
	mt->height = 1080;
	if (!mt)
		error();
	if (ac != 2)
	{
		free(mt);
		p_error();
	}
	init_mt(mt);
	mt->gr.mlx = mlx_init(mt->width, mt->height, "miniRT", true);
	if (!mt->gr.mlx)
	{
		free(mt);
		m_error();
	}
	mt->gr.img = mlx_new_image(mt->gr.mlx, mt->width, mt->height);
	if (!mt->gr.img)
	{
		free(mt);
		free(mt->gr.mlx);
		error();
	}

	parser(mt, av[1]);
	//exit(1);
	printf("A: %f %i,%i,%i\n", mt->scene.a_light.ratio, mt->scene.a_light.color.r, mt->scene.a_light.color.g, mt->scene.a_light.color.b);
	printf("C: %f,%f,%f %f,%f,%f %i\n", mt->scene.camera.origin.x, mt->scene.camera.origin.y, mt->scene.camera.origin.z, mt->scene.camera.direction.x, mt->scene.camera.direction.y, mt->scene.camera.direction.z, mt->scene.camera.fov);
	printf("L: %f,%f,%f %f %i,%i,%i\n", mt->scene.light.coord.x, mt->scene.light.coord.y, mt->scene.light.coord.z, mt->scene.light.bright, mt->scene.light.color.r, mt->scene.light.color.g, mt->scene.light.color.b);
	t_sphere *temp;
	while (mt->obj.sphere)
	{
		temp = mt->obj.sphere->content;
		printf("sp:  %f,%f,%f %f %i,%i,%i\n", temp->center.x, temp->center.y, temp->center.z, temp->diam, temp->color.r, temp->color.g, temp->color.b);
		free (temp);
		mt->obj.sphere = mt->obj.sphere->next;
	}
	
	
	mt->vp.aspect_ratio = (float)mt->width / (float)mt->height;
	mt->vp.height = 2 * tanf((mt->scene.camera.fov / 2) * (M_PI / 180)); // Vertical FOV
	mt->vp.width = mt->vp.height * mt->vp.aspect_ratio;
	mt->vp.x_pix = mt->vp.width / mt->width;
	mt->vp.y_pix = mt->vp.height / mt->height;
	
	// memset(mt->gr.img->pixels, 200, mt->gr.img->width * mt->gr.img->height * BPP);

	draw_scene(mt);
	if (mlx_image_to_window(mt->gr.mlx, mt->gr.img, 0, 0) < 0)
		error();
	mlx_loop_hook(mt->gr.mlx, hook, mt);
	mlx_resize_hook(mt->gr.mlx, resize, mt);	 // 
	// mlx_scroll_hook(mt->gr.mlx, scrollhook, mt);
	mlx_loop(mt->gr.mlx);
	mlx_delete_image(mt->gr.mlx, mt->gr.img);
	mlx_terminate(mt->gr.mlx);
	free_list(mt->obj.sphere);
	free(mt->obj.cylinder);
	free(mt->obj.plane);
	free(mt);
	return (EXIT_SUCCESS);
}
