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

void error(void)
{
	write(STDERR_FILENO, "Error: allocation failed\n", 25);
	exit(EXIT_FAILURE);
}

void	init_mt(t_minirt *mt)
{
	mt->scene.a_light.ratio = 0.0;
	mt->scene.a_light.color.r = 0;
	mt->scene.a_light.color.g = 0;
	mt->scene.a_light.color.b = 0;
	mt->scene.camera.origin.x = 0.0;
	mt->scene.camera.origin.y = 0.0;
	mt->scene.camera.origin.z = 0.0;
	mt->scene.camera.direction.x = 0.0;
	mt->scene.camera.direction.y = 0.0;
	mt->scene.camera.direction.z = 0.0;
	mt->scene.light.bright = 0.0;
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
	mt->scene.camera.up_v = cross_prod_vec(mt->scene.camera.forward_w, mt->scene.camera.right_u);
	// Add 4th row to a matrix?
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

	// t_sphere sp;
	// sp.center.x = 0.0;
	// sp.center.y = -10.0;
	// sp.center.z = -120.0;
	// sp.diam = 40;
	// sp.color.r = 255;
	// sp.color.g = 0;
	// sp.color.b = 0;
	// ft_lstadd_back(&mt->obj.sphere, ft_lstnew(&sp));
	// t_sphere	sp2;
	// sp2.center.x = 20.0;
	// sp2.center.y = -8.0;
	// sp2.center.z = -100.0;
	// sp2.diam = 20.0;
	// sp2.color.r = 150;
	// sp2.color.g = 150;
	// sp2.color.b = 255;
	// ft_lstadd_back(&mt->obj.sphere, ft_lstnew(&sp2));
	// t_sphere	sp3;
	// sp3.center.x = 20.0;
	// sp3.center.y = 15.0;
	// sp3.center.z = -120.0;
	// sp3.diam = 10.0;
	// sp3.color.r = 150;
	// sp3.color.g = 150;
	// sp3.color.b = 150;
	// ft_lstadd_back(&mt->obj.sphere, ft_lstnew(&sp3));
	// t_plane	pl;
	// pl.coord.x = 0.0;
	// pl.coord.y = -30.0;
	// pl.coord.z = 0.0;
	// // Normalized vector ! Check for the range [-1, 1]
	// pl.orientation.x = 0.0;
	// pl.orientation.y = 1.0;
	// pl.orientation.z = 0.0;
	// pl.color.r = 255;
	// pl.color.g = 0;
	// pl.color.b = 255;
	// ft_lstadd_back(&mt->obj.plane, ft_lstnew(&pl));
	// t_cylinder cy;
	// cy.coordinates.x = -40.0;
	// cy.coordinates.y = -20;
	// cy.coordinates.z = -100;
	// // Normalized vector ! Check for the range [-1, 1]
	// cy.orientation.x = 0.0;
	// cy.orientation.y = 1.0;
	// cy.orientation.z = 0.0;
	// cy.diameter = 20.0;
	// cy.height = 15.0;
	// cy.color.r = 100;
	// cy.color.g = 200;
	// cy.color.b = 255;
	// ft_lstadd_back(&mt->obj.cylinder, ft_lstnew(&cy));
	// mt->scene.a_light.ratio = 0.1;
	// mt->scene.a_light.color.r = 255;
	// mt->scene.a_light.color.g = 255;
	// mt->scene.a_light.color.b = 255;
	// mt->scene.camera.origin.x = 0;
	// mt->scene.camera.origin.y = 0;
	// mt->scene.camera.origin.z = 0;
	// mt->scene.camera.direction.x = 0.0;
	// mt->scene.camera.direction.y = 0.0;
	// mt->scene.camera.direction.z = -1.0;
	// mt->scene.camera.fov = 80.0;

	// calculate_camera(mt, mt->scene.camera.origin, mt->scene.camera.direction);
	calculate_camera(mt);

	//No color in mandatory part
	// mt->scene.light.bright = 0.9;
	// mt->scene.light.coord.x = 0.0;
	// mt->scene.light.coord.y = 80.0;
	// mt->scene.light.coord.z = -100.0;
	// mt->scene.light.color.r = 255;
	// mt->scene.light.color.g = 255;
	// mt->scene.light.color.b = 255;
	
	// mt->vp.aspect_ratio = (float)mt->width / (float)mt->height;
	// mt->vp.height = 2 * tanf(mt->scene.camera.fov * 0.5 * (M_PI / 180));
	// mt->vp.height = tanf(mt->scene.camera.fov * 0.5 * (M_PI / 180));
	// mt->vp.width = mt->vp.height * mt->vp.aspect_ratio;
	// mt->vp.x_pix = mt->vp.width / mt->width;
	// mt->vp.y_pix = mt->vp.height / mt->height;
	
	// memset(mt->gr.img->pixels, 200, mt->gr.img->width * mt->gr.img->height * BPP);

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
	free(mt->obj.cylinder);
	free(mt->obj.plane);
	free(mt);
	return (EXIT_SUCCESS);
}
