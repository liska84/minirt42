#include "minirt.h"

void	rotate_cam_y(t_minirt *mt, double y)
{
	t_vector	direction;

	// printf("camera origin: [x%f y%f z%f]\n", mt->scene.camera.origin.x,
	// 	mt->scene.camera.origin.y, mt->scene.camera.origin.z);
	// printf("camera direction: [x%f y%f z%f]\n", mt->scene.camera.direction.x,
	// 	mt->scene.camera.direction.y, mt->scene.camera.direction.z);
	// printf("Rotate camera by y\n");
	mult_vec(&mt->scene.camera.right_u, y);
	direction = add_vec(mt->scene.camera.direction, mt->scene.camera.right_u);
	normalize_vec(&direction);
	mt->scene.camera.direction = direction;
	calculate_camera(mt);
	// printf("camera origin: [x%f y%f z%f]\n", mt->scene.camera.origin.x,
	// 	mt->scene.camera.origin.y, mt->scene.camera.origin.z);
	// printf("camera direction: [x%f y%f z%f]\n", mt->scene.camera.direction.x,
	// 	mt->scene.camera.direction.y, mt->scene.camera.direction.z);
	draw_scene(mt);
}

void	rotate_cam_x(t_minirt *mt, double x)
{
	t_vector	direction;

	// printf("camera origin: [x%f y%f z%f]\n", mt->scene.camera.origin.x,
	// 	mt->scene.camera.origin.y, mt->scene.camera.origin.z);
	// printf("camera direction: [x%f y%f z%f]\n", mt->scene.camera.direction.x,
	// 	mt->scene.camera.direction.y, mt->scene.camera.direction.z);
	// printf("Rotate camera by x\n");
	mult_vec(&mt->scene.camera.up_v, x);
	direction = add_vec(mt->scene.camera.direction, mt->scene.camera.up_v);
	normalize_vec(&direction);
	mt->scene.camera.direction = direction;
	calculate_camera(mt);
	// printf("camera origin: [x%f y%f z%f]\n", mt->scene.camera.origin.x,
	// 	mt->scene.camera.origin.y, mt->scene.camera.origin.z);
	// printf("camera direction: [x%f y%f z%f]\n", mt->scene.camera.direction.x,
	// 	mt->scene.camera.direction.y, mt->scene.camera.direction.z);
	draw_scene(mt);
}

void	rotate_cam_z(t_minirt *mt, double z)
{
	t_vector	direction;

	// printf("camera origin: [x%f y%f z%f]\n", mt->scene.camera.origin.x,
	// 	mt->scene.camera.origin.y, mt->scene.camera.origin.z);
	// printf("camera direction: [x%f y%f z%f]\n", mt->scene.camera.direction.x,
	// 	mt->scene.camera.direction.y, mt->scene.camera.direction.z);
	// printf("Rotate camera by x\n");
	printf("Z %f\n", z);
	printf("Vector: x%fy%fz%f\n", mt->scene.camera.forward_w.x, mt->scene.camera.forward_w.y, mt->scene.camera.forward_w.z);

	mult_vec(&mt->scene.camera.forward_w, z);

	printf("Vector: x%fy%fz%f\n", mt->scene.camera.forward_w.x, mt->scene.camera.forward_w.y, mt->scene.camera.forward_w.z);

	printf("***\n");
	
	printf("Vector: x%fy%fz%f\n", mt->scene.camera.direction.x, mt->scene.camera.direction.y, mt->scene.camera.direction.z);

	direction = add_vec(mt->scene.camera.direction, mt->scene.camera.forward_w);

		printf("Direction: x%fy%fz%f\n", direction.x, direction.y, direction.z);


	normalize_vec(&direction);
	mt->scene.camera.direction = direction;
	calculate_camera(mt);
	// printf("camera origin: [x%f y%f z%f]\n", mt->scene.camera.origin.x,
	// 	mt->scene.camera.origin.y, mt->scene.camera.origin.z);
	// printf("camera direction: [x%f y%f z%f]\n", mt->scene.camera.direction.x,
	// 	mt->scene.camera.direction.y, mt->scene.camera.direction.z);
	draw_scene(mt);
}

// void	transformation(t_minirt *mt)
// {
// 	;
// }

void	intro(t_minirt *mt)
{
	t_list *head; 
	t_sphere	*sp;
	t_cylinder	*cy;
	int s = 0;
	int c = 0;

	if (mt->obj.cylinder)
	{
		head = mt->obj.cylinder;
		while(head)
		{
			cy = head->content;
			printf("Cylinder: origin (%.2f, %.2f, %2.2f), orientation (%.2f, %.2f, %.2f)\n", cy->coord.x, cy->coord.y, cy->coord.z, cy->orien.x, cy->orien.y, cy->orien.z);
			c++;
			head = head->next;
		}
	}
	if (mt->obj.sphere)
	{
		head = mt->obj.sphere;
		while (head)
		{
			sp = head->content;
			printf("Sphere: origin (%.2f, %.2f,%.2f)\n", sp->center.x, sp->center.y, sp->center.z);
			s++;
			head = head->next;
		}
	}
	printf("There are %d cylinder(s) and %d sphere(s). Which object to transform?\n", c, s);
	printf("For cylinder press 1, for shpere press 2\n");
}


// void	translation(t_minirt *mt, int object)
// {
// 	if (object == 2)
// 	{
// 		;
// 	}
// }


void keyhook(mlx_key_data_t keydata, void* param)
{
	t_minirt	*mt;
	int			obj = 0;

	mt = param;
	if (keydata.key == MLX_KEY_LEFT_SUPER && keydata.action == MLX_PRESS)
		intro(mt);
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
	{
		printf("Transforming cylinder\n");
		printf("For rotation press R, for translation press T\n");
		obj = 1;
	}
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
	{
		printf("Transforming sphere\n");
		printf("For this type of object onle translation is available, press T\n");
		obj = 2;
	}
	// if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	// 	translation(mt, obj);
	// if (keydata.key == MLX_KEY_T && keydata.action == MLX_PRESS)
	// 	;
}

void	hook(void *param)
{
	t_minirt	*mt;


	mt = param;

	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mt->gr.mlx);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_Q))
		move_cam_y(mt, 1);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_A))
		move_cam_y(mt, -1);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_W))
		move_cam_x(mt, 1);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_S))
		move_cam_x(mt, -1);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_E))
		move_cam_z(mt, 1);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_D))
		move_cam_z(mt, -1);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_R))
		rotate_cam_y(mt, 0.4);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_F))
		rotate_cam_y(mt, -0.4);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_T))
		rotate_cam_x(mt, 0.4);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_G))
		rotate_cam_x(mt, -0.4);
	// if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_T))
	// 	rotate_cam_z(mt, 0.4);
	// if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_G))
	// 	rotate_cam_z(mt, -0.4);


}
