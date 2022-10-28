#include "minirt.h"

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

void	calculate_camera(t_minirt *mt)
{
	t_vector	tmp;

	mt->scene.camera.forward_w = mt->scene.camera.direction;
	mult_vec(&mt->scene.camera.forward_w, -1);
	normalize_vec(&mt->scene.camera.forward_w);
	tmp = new_vec(0, 1, 0);
	mt->scene.camera.right_u = cross_prod_vec(tmp, mt->scene.camera.forward_w);
	normalize_vec(&mt->scene.camera.right_u);
		mt->scene.camera.up_v = cross_prod_vec(mt->scene.camera.forward_w,
			mt->scene.camera.right_u);
	printf("Camera position:\t[%.2f, %.2f, %.2f]\n",
		mt->scene.camera.origin.x, mt->scene.camera.origin.y,
		mt->scene.camera.origin.z);
	printf("Camera direction:\t[%.2f, %.2f, %.2f]\n",
		mt->scene.camera.direction.x, mt->scene.camera.direction.y,
		mt->scene.camera.direction.z);
}

void	leaks(void)
{
	system("leaks miniRT");
}

int	main(int ac, char **av)
{
	t_minirt	*mt;

	atexit(leaks);
	mt = malloc(sizeof(t_minirt));
	if (!mt)
		error();
	mt->width = 1920;
	mt->height = 1080;
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
	calculate_camera(mt);
	draw_scene(mt);
	if (mlx_image_to_window(mt->gr.mlx, mt->gr.img, 0, 0) < 0)
		error();
	mlx_loop_hook(mt->gr.mlx, hook, mt);
	mlx_resize_hook(mt->gr.mlx, resize, mt);
	mlx_scroll_hook(mt->gr.mlx, scrollhook, mt);
	mlx_loop(mt->gr.mlx);
	mlx_delete_image(mt->gr.mlx, mt->gr.img);
	mlx_terminate(mt->gr.mlx);
	free_list(mt->obj.sphere);
	free_list(mt->obj.cylinder);
	free_list(mt->obj.plane);
	free(mt);
	return (EXIT_SUCCESS);
}
