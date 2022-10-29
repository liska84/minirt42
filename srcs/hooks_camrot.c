#include "minirt.h"

void	scrollhook(double xdelta, double ydelta, void *param)
{
	t_minirt	*mt;

	(void)xdelta;
	mt = param;
	if (ydelta > 0)
	{
		printf("\033[1;35mZOOM -\033[0m\n");
		mt->scene.camera.fov += (float)ydelta;
	}
	if (ydelta < 0)
	{
		printf("\033[1;35mZOOM +\033[0m\n");
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

/*Camera rotation*/
void	rotate_cam_y(t_minirt *mt, double y)
{
	float	sin;
	float	cos;
	float	tmp;

	printf("\033[1;91mRotating camera camera by Y\033[0m\n");
	sin = sinf(y * (M_PI / 180.0));
	cos = cosf(y * (M_PI / 180.0));
	tmp = cos * mt->scene.camera.direction.x
		+ sin * mt->scene.camera.direction.z;
	mt->scene.camera.direction.z = -sin * mt->scene.camera.direction.x
		+ cos * mt->scene.camera.direction.z;
	mt->scene.camera.direction.x = tmp;
	normalize_vec(&mt->scene.camera.direction);
	calculate_camera(mt);
	draw_scene(mt);
}

void	rotate_cam_x(t_minirt *mt, double x)
{
	float	sin;
	float	cos;
	float	tmp;

	printf("\033[1;95mRotating camera camera by Y\033[0m\n");
	sin = sinf(x * (M_PI / 180.0));
	cos = cosf(x * (M_PI / 180.0));
	tmp = cos * mt->scene.camera.direction.y
		+ -sin * mt->scene.camera.direction.z;
	mt->scene.camera.direction.z = sin * mt->scene.camera.direction.y
		+ cos * mt->scene.camera.direction.z;
	mt->scene.camera.direction.y = tmp;
	normalize_vec(&mt->scene.camera.direction);
	calculate_camera(mt);
	draw_scene(mt);
}
