#include "minirt.h"

void scrollhook(double xdelta, double ydelta, void* param)
{
	t_minirt *mt;

	(void)xdelta;
	mt = param;
	printf("ydelta %f\n", ydelta);
	if (ydelta > 0)
	{
		puts("Zoom out!");
		mt->scene.camera.fov += (float)ydelta;
		if (mt->scene.camera.fov < 1.0)
			mt->scene.camera.fov = 1.0;
		else if (mt->scene.camera.fov > 180.0)
			mt->scene.camera.fov = 180.0;
		printf("FOV: %f\n", mt->scene.camera.fov);
		mt->vp.height = tanf(mt->scene.camera.fov * 0.5 * (M_PI / 180));
		mt->vp.width = mt->vp.height * mt->vp.aspect_ratio;
	}
	if (ydelta < 0)
	{
		puts("Zoom in!");
		mt->scene.camera.fov += (float)ydelta;
		if (mt->scene.camera.fov < 1.0)
			mt->scene.camera.fov = 1.0;
		else if (mt->scene.camera.fov > 180.0)
			mt->scene.camera.fov = 180.0;
		printf("FOV: %f\n", mt->scene.camera.fov);
		mt->vp.height = tanf(mt->scene.camera.fov * 0.5 * (M_PI / 180));
		mt->vp.width = mt->vp.height * mt->vp.aspect_ratio;
	}
	draw_scene(mt);
}

void resize(int32_t width, int32_t height, void* param)
{
	t_minirt *mt;

	mt = param;
	mt->height = height;
	mt->width = width;
	mt->vp.aspect_ratio = (float)mt->width / (float)mt->height;
	draw_scene(mt);
}

void	hook(void *param)
{
	t_minirt *mt;

	mt = param;
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mt->gr.mlx);

	// if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_Q))
	// 	move_cam_y(-1, mt);
	// if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_A))
	// 	move_cam_y(1, mt);
	// if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_W))
	// 	move_cam_x(-1, mt);
	// if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_H))
	// 	move_cam_x(1, mt);
	// if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_Z))
	// 	move_cam_z(1, mt);
	// if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_X))
	// 	move_cam_z(-1, mt);


	// if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_EQUAL))
	// 	zoom(5, mt);
	// if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_MINUS))
	// 	zoom(-5, mt);
}
