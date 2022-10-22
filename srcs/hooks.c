#include "minirt.h"

void scrollhook(double xdelta, double ydelta, void* param)
{
	t_minirt *mt;

	(void)xdelta;
	mt = param;
	printf("ydelta %f\n", ydelta);
	if (ydelta > 0)
	{
		printf("Zoom out!");
		mt->scene.camera.fov += (float)ydelta;
	}
	if (ydelta < 0)
	{
		printf("Zoom in!");
		mt->scene.camera.fov += (float)ydelta;
	}
	if (mt->scene.camera.fov < 1.0)
		mt->scene.camera.fov = 1.0;
	else if (mt->scene.camera.fov > 180.0)
		mt->scene.camera.fov = 180.0;
	printf("FOV: %d\n", mt->scene.camera.fov);
	draw_scene(mt);
}

void resize(int32_t width, int32_t height, void* param)
{
	t_minirt *mt;

	mt = param;
	mt->height = height;
	mt->width = width;
	printf("Aspect ratio: %f\n", (double)mt->width / (double)mt->height);
	draw_scene(mt);
}

void	move_cam_y(t_minirt *mt, int y)
{
	printf("Moving camera by y\n");
	mult_vec(&mt->scene.camera.up_v, y);
	normalize_vec(&mt->scene.camera.up_v);
	mt->scene.camera.origin = add_vec(mt->scene.camera.origin, mt->scene.camera.up_v);
	calculate_camera(mt);
	draw_scene(mt);
}

void	move_cam_x(t_minirt *mt, int x)
{
	printf("Moving camera by x\n");
	mult_vec(&mt->scene.camera.right_u, x);
	mt->scene.camera.origin = add_vec(mt->scene.camera.origin, mt->scene.camera.right_u);
	calculate_camera(mt);
	draw_scene(mt);
}

void	move_cam_z(t_minirt *mt, int z)
{
	printf("Moving camera by z\n");
	mult_vec(&mt->scene.camera.forward_w, z);
	mt->scene.camera.origin = add_vec(mt->scene.camera.origin, mt->scene.camera.forward_w);
	calculate_camera(mt);
	draw_scene(mt);
}

void	rotate_cam_y(t_minirt *mt, double y)
{
	t_vector	direction;

	printf("camera origin: [x%f y%f z%f]\n", mt->scene.camera.origin.x, mt->scene.camera.origin.y, mt->scene.camera.origin.z);
	printf("camera direction: [x%f y%f z%f]\n", mt->scene.camera.direction.x, mt->scene.camera.direction.y, mt->scene.camera.direction.z);
	printf("Rotate camera by y\n"); 
	
	mult_vec(&mt->scene.camera.right_u, y);
	direction = add_vec(mt->scene.camera.direction, mt->scene.camera.right_u);
	normalize_vec(&direction);
	mt->scene.camera.direction = direction;
	calculate_camera(mt);
	
	printf("camera origin: [x%f y%f z%f]\n", mt->scene.camera.origin.x, mt->scene.camera.origin.y, mt->scene.camera.origin.z);
	printf("camera direction: [x%f y%f z%f]\n", mt->scene.camera.direction.x, mt->scene.camera.direction.y, mt->scene.camera.direction.z);
	draw_scene(mt);
}

void	rotate_cam_x(t_minirt *mt, double x)
{
	t_vector	direction;

	printf("camera origin: [x%f y%f z%f]\n", mt->scene.camera.origin.x, mt->scene.camera.origin.y, mt->scene.camera.origin.z);
	printf("camera direction: [x%f y%f z%f]\n", mt->scene.camera.direction.x, mt->scene.camera.direction.y, mt->scene.camera.direction.z);
	printf("Rotate camera by x\n");
	mult_vec(&mt->scene.camera.up_v, x);
	direction = add_vec(mt->scene.camera.direction, mt->scene.camera.up_v);
	normalize_vec(&direction);
	mt->scene.camera.direction = direction;
	calculate_camera(mt);
	printf("camera origin: [x%f y%f z%f]\n", mt->scene.camera.origin.x, mt->scene.camera.origin.y, mt->scene.camera.origin.z);
	printf("camera direction: [x%f y%f z%f]\n", mt->scene.camera.direction.x, mt->scene.camera.direction.y, mt->scene.camera.direction.z);
	draw_scene(mt);
}

void	hook(void *param)
{
	t_minirt *mt;

	mt = param;
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mt->gr.mlx);

	// Camera position 
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

	// Camera direction
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_R))
		rotate_cam_y(mt, 0.2);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_F))
		rotate_cam_y(mt, -0.2);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_T))
		rotate_cam_x(mt, 0.1);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_G))
		rotate_cam_x(mt, -0.1);
}
