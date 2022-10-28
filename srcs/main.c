#include "minirt.h"

void	free_list(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->content);
		free(tmp);
	}
}

void	leaks(void)
{
	system("leaks miniRT");
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

t_vector	mat3vec(t_matrix matrix, t_vector vector)
{
	t_vector tmp; 

	tmp.x = matrix.row1.x * vector.x + matrix.row1.y * vector.y + matrix.row1.z;
	tmp.y = matrix.row2.x * vector.x + matrix.row2.y * vector.y + matrix.row2.z;
	tmp.z = matrix.row3.x * vector.x + matrix.row3.y * vector.y + matrix.row3.z;
	return (tmp);
}

/*Negate the direction vector! For matrix Z should be positive*/
void	calculate_camera(t_minirt *mt)
{
	t_vector	tmp;
	t_matrix	camtoworld;

	mt->scene.camera.forward_w = mt->scene.camera.direction;
	mult_vec(&mt->scene.camera.forward_w, -1);
	normalize_vec(&mt->scene.camera.forward_w);
	tmp = new_vec(0, 1, 0);
	mt->scene.camera.right_u = cross_prod_vec(tmp, mt->scene.camera.forward_w);
	normalize_vec(&mt->scene.camera.right_u);
	// mt->scene.camera.right_u.x = 0;
	// mt->scene.camera.right_u.y = -1;
	mt->scene.camera.up_v = cross_prod_vec(mt->scene.camera.forward_w, mt->scene.camera.right_u);
	// mt->scene.camera.up_v.x = 1;
	// mt->scene.camera.up_v.y = 0;
	
	camtoworld.row1 = new_vec(mt->scene.camera.right_u.x, mt->scene.camera.right_u.y, mt->scene.camera.right_u.z);
	camtoworld.row2 = new_vec(mt->scene.camera.up_v.x, mt->scene.camera.up_v.y, mt->scene.camera.up_v.z);
	camtoworld.row3 = new_vec(mt->scene.camera.forward_w.x, mt->scene.camera.forward_w.y, mt->scene.camera.forward_w.z);
	// // camtoworld.row4 = new_vec(0, 0, 0, 1);
	mt->scene.camera.cam2world = camtoworld;
	printf("(%f, %f, %f)\n", mt->scene.camera.right_u.x, mt->scene.camera.right_u.y, mt->scene.camera.right_u.z);
	printf("(%f, %f, %f)\n", mt->scene.camera.up_v.x, mt->scene.camera.up_v.y, mt->scene.camera.up_v.z);
	printf("(%f, %f, %f)\n", mt->scene.camera.forward_w.x, mt->scene.camera.forward_w.y, mt->scene.camera.forward_w.z);
}

int	main(int ac, char **av)
{
	t_minirt	*mt;
	// t_cylinder	*ptr3;
	// t_list		*head;
	// t_plane		*ptr;
	// t_sphere	*ptr2;

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
	// printf("A: %f %i,%i,%i\n", mt->scene.a_light.ratio,
	// 	mt->scene.a_light.color.r,
	// 	mt->scene.a_light.color.g, mt->scene.a_light.color.b);
	// printf("C: %f,%f,%f %f,%f,%f %i\n", mt->scene.camera.origin.x,
	// 	mt->scene.camera.origin.y,
	// 	mt->scene.camera.origin.z, mt->scene.camera.direction.x,
	// 	mt->scene.camera.direction.y,
	// 	mt->scene.camera.direction.z, mt->scene.camera.fov);
	// printf("L: %f,%f,%f %f %i,%i,%i\n",
	// 	mt->scene.light.coord.x, mt->scene.light.coord.y,
	// 	mt->scene.light.coord.z, mt->scene.light.bright,
	// 	mt->scene.light.color.r,
	// 	mt->scene.light.color.g, mt->scene.light.color.b);
	// head = mt->obj.plane;
	// while (head)
	// {
	// 	ptr = head->content;
	// 	printf("Plane - origin: (%f, %f,%f), orien: (%f, %f, %f)\n",
	// 		ptr->coord.x, ptr->coord.y,
	// 		ptr->coord.z, ptr->orien.x, ptr->orien.y, ptr->orien.z);
	// 	head = head->next;
	// }
	// head = mt->obj.sphere;
	// while (head)
	// {
	// 	ptr2 = head->content;
	// 	printf("Sphere - C: (%f, %f,%f), D: %f\n", ptr2->center.x,
	// 		ptr2->center.y, ptr2->center.z, ptr2->diam);
	// 	head = head->next;
	// }
	// head = mt->obj.cylinder;
	// while (head)
	// {
	// 	ptr3 = head->content;
	// 	printf("Cylinder - origin: (%f, %f,%f), orien: (%f, %f, %f),"
	// 		"D:%f, H: %f\n",
	// 		ptr3->coord.x, ptr3->coord.y,
	// 		ptr3->coord.z, ptr3->orien.x,
	// 		ptr3->orien.y, ptr3->orien.z, ptr3->diameter, ptr3->height);
	// 	head = head->next;
	// }
	calculate_camera(mt);
	draw_scene(mt);
	if (mlx_image_to_window(mt->gr.mlx, mt->gr.img, 0, 0) < 0)
		error();
	mlx_loop_hook(mt->gr.mlx, hook, mt);
	mlx_resize_hook(mt->gr.mlx, resize, mt);
	mlx_scroll_hook(mt->gr.mlx, scrollhook, mt);
	// mlx_key_hook(mt->gr.mlx, &keyhook, mt);
	mlx_loop(mt->gr.mlx);
	mlx_delete_image(mt->gr.mlx, mt->gr.img);
	mlx_terminate(mt->gr.mlx);
	free_list(mt->obj.sphere);
	free_list(mt->obj.cylinder);
	free_list(mt->obj.plane);
	free(mt);
	return (EXIT_SUCCESS);
}
