#include "minirt.h"

void	rotate_cam_y(t_minirt *mt, double y)
{
	t_vector	direction;

	printf("camera origin: [x%f y%f z%f]\n", mt->scene.camera.origin.x,
		mt->scene.camera.origin.y, mt->scene.camera.origin.z);
	printf("camera direction: [x%f y%f z%f]\n", mt->scene.camera.direction.x,
		mt->scene.camera.direction.y, mt->scene.camera.direction.z);
	printf("Rotate camera by y\n");
	mult_vec(&mt->scene.camera.right_u, y);
	direction = add_vec(mt->scene.camera.direction, mt->scene.camera.right_u);
	normalize_vec(&direction);
	mt->scene.camera.direction = direction;
	calculate_camera(mt);
	printf("camera origin: [x%f y%f z%f]\n", mt->scene.camera.origin.x,
		mt->scene.camera.origin.y, mt->scene.camera.origin.z);
	printf("camera direction: [x%f y%f z%f]\n", mt->scene.camera.direction.x,
		mt->scene.camera.direction.y, mt->scene.camera.direction.z);
	draw_scene(mt);
}

void	rotate_cam_x(t_minirt *mt, double x)
{
	t_vector	direction;

	mult_vec(&mt->scene.camera.up_v, x);
	direction = add_vec(mt->scene.camera.direction, mt->scene.camera.up_v);
	normalize_vec(&direction);
	mt->scene.camera.direction = direction;
	calculate_camera(mt);
	draw_scene(mt);
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
}
