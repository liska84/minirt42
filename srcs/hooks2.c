#include "minirt.h"

void	scrollhook(double xdelta, double ydelta, void *param)
{
	t_minirt	*mt;

	(void)xdelta;
	mt = param;
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
	draw_scene(mt);
}

void	resize(int32_t width, int32_t height, void *param)
{
	t_minirt	*mt;

	mt = param;
	mt->height = height;
	mt->width = width;
	draw_scene(mt);
}

/* Camera translation*/

void	move_cam_y(t_minirt *mt, int y)
{
	printf("Moving camera by y\n");
	mult_vec(&mt->scene.camera.up_v, y);
	normalize_vec(&mt->scene.camera.up_v);
	mt->scene.camera.origin
		= add_vec(mt->scene.camera.origin, mt->scene.camera.up_v);
	calculate_camera(mt);
	draw_scene(mt);
}

void	move_cam_x(t_minirt *mt, int x)
{
	printf("Moving camera by x\n");
	mult_vec(&mt->scene.camera.right_u, x);
	mt->scene.camera.origin
		= add_vec(mt->scene.camera.origin, mt->scene.camera.right_u);
	calculate_camera(mt);
	draw_scene(mt);
}

void	move_cam_z(t_minirt *mt, int z)
{
	printf("Moving camera by z\n");
	mult_vec(&mt->scene.camera.forward_w, z);
	mt->scene.camera.origin
		= add_vec(mt->scene.camera.origin, mt->scene.camera.forward_w);
	calculate_camera(mt);
	draw_scene(mt);
}
