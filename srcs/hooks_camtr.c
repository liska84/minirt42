#include "minirt.h"

/* Camera translation*/
void	move_cam_y(t_minirt *mt, int y)
{
	printf("\033[1;94mMoving camera by Y\033[0m\n");
	mult_vec(&mt->scene.camera.up_v, y);
	mt->scene.camera.origin
		= add_vec(mt->scene.camera.origin, mt->scene.camera.up_v);
	calculate_camera(mt);
	draw_scene(mt);
}

void	move_cam_x(t_minirt *mt, int x)
{
	printf("\033[1;93mMoving camera by X\033[0m\n");
	mult_vec(&mt->scene.camera.right_u, x);
	mt->scene.camera.origin
		= add_vec(mt->scene.camera.origin, mt->scene.camera.right_u);
	calculate_camera(mt);
	draw_scene(mt);
}

void	move_cam_z(t_minirt *mt, int z)
{
	printf("\033[1;92mMoving camera by Z\033[0m\n");
	mult_vec(&mt->scene.camera.forward_w, z);
	mt->scene.camera.origin
		= add_vec(mt->scene.camera.origin, mt->scene.camera.forward_w);
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
		move_cam_y(mt, 10);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_E))
		move_cam_y(mt, -10);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_A))
		move_cam_x(mt, 10);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_D))
		move_cam_x(mt, -10);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_S))
		move_cam_z(mt, 10);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_W))
		move_cam_z(mt, -10);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_LEFT))
		rotate_cam_y(mt, 30);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_RIGHT))
		rotate_cam_y(mt, -30);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_UP))
		rotate_cam_x(mt, 30);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_DOWN))
		rotate_cam_x(mt, -30);
}
