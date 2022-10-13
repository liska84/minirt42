#include "minirt.h"

// static void move_cam_x(int x_axis, t_minirt *mt)
// {
// 	t_sphere	*sp;
// 	t_plane		*pl;
// 	t_cylinder	*cy;
// 	t_list		*ptr = NULL;
// 	int x = x_axis * 5;

// 	if (mt->obj.sphere)
// 	{
// 		ptr = mt->obj.sphere;
// 		while (ptr)
// 		{
// 			sp = ptr->content;
// 			sp->center.x -= x; 
// 			ptr = ptr->next;
// 		}
// 	}
// 	if (mt->obj.plane)
// 	{
// 		ptr = mt->obj.plane;
// 		while (ptr)
// 		{
// 			pl = ptr->content;
// 			pl->coord.x -= x;
// 			ptr = ptr->next;
// 		}
// 	}
// 	if (mt->obj.cylinder)
// 	{
// 		ptr = mt->obj.cylinder;
// 		while (ptr)
// 		{
// 			cy = ptr->content;
// 			cy->coordinates.x -= x;
// 			ptr = ptr->next;
// 		}	
// 	}
// 	draw_scene(mt);
// }

// static void move_cam_y(int y_axis, t_minirt *mt)
// {
// 	t_sphere	*sp;
// 	t_plane		*pl;
// 	t_cylinder	*cy;
// 	t_list		*ptr = NULL;
// 	int y = y_axis * 5;

// 	if (mt->obj.sphere)
// 	{
// 		ptr = mt->obj.sphere;
// 		while (ptr)
// 		{
// 			sp = ptr->content;
// 			sp->center.y -= y; 
// 			ptr = ptr->next;
// 		}
// 	}
// 	if (mt->obj.plane)
// 	{
// 		ptr = mt->obj.plane;
// 		while (ptr)
// 		{
// 			pl = ptr->content;
// 			pl->coord.y -= y;
// 			ptr = ptr->next;
// 		}
// 	}
// 	if (mt->obj.cylinder)
// 	{
// 		ptr = mt->obj.cylinder;
// 		while (ptr)
// 		{
// 			cy = ptr->content;
// 			cy->coordinates.y -= y;
// 			ptr = ptr->next;
// 		}	
// 	}
// 	draw_scene(mt);
// }

// static void move_cam_z(int z_axis, t_minirt *mt)
// {
// 	t_sphere	*sp;
// 	t_plane		*pl;
// 	t_cylinder	*cy;
// 	t_list		*ptr = NULL;
// 	int z = z_axis * 5;

// 	if (mt->obj.sphere)
// 	{
// 		ptr = mt->obj.sphere;
// 		while (ptr)
// 		{
// 			sp = ptr->content;
// 			sp->center.z += z; 
// 			ptr = ptr->next;
// 		}
// 	}
// 	if (mt->obj.plane)
// 	{
// 		ptr = mt->obj.plane;
// 		while (ptr)
// 		{
// 			pl = ptr->content;
// 			pl->coord.z += z;
// 			ptr = ptr->next;
// 		}
// 	}
// 	if (mt->obj.cylinder)
// 	{
// 		ptr = mt->obj.cylinder;
// 		while (ptr)
// 		{
// 			cy = ptr->content;
// 			cy->coordinates.z += z;
// 			ptr = ptr->next;
// 		}	
// 	}
// 	draw_scene(mt);
// }

// Check for max min degree?
void	zoom(int angle, t_minirt *mt)
{
	mt->scene.camera.fov -= angle;
	mt->vp.height = 2 * tanf((mt->scene.camera.fov * 0.5) * (M_PI / 180));
	mt->vp.width = mt->vp.height * mt->vp.aspect_ratio;
	mt->vp.x_pix = mt->vp.width / mt->width;
	mt->vp.y_pix = mt->vp.height / mt->height;
	draw_scene(mt);
}

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

void	translate(t_minirt *mt, float x, float y, float z)
{
	float		matrix[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
	t_vector	new;
	
	new.x = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z;
	new.y = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z;
	new.z = matrix[2][0] * x + matrix[2][1] * y + matrix[2][2] * z;
	mt->scene.camera.origin = new;
	draw_scene(mt);
}

void	hook(void *param)
{
	t_minirt *mt;

	mt = param;
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mt->gr.mlx);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_Q))
		translate(mt, 0, -1, 0);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_A))
		translate(mt, 0, 1, 0);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_W))
		translate(mt, -1, 0, 0);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_S))
		translate(mt, 1, 0, 0);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_E))
		translate(mt, 1, 0, 1);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_D))
		translate(mt, 1, 0, -1);
	// if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_Q))
	// 	move_cam_y(-1, mt);
	// if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_A))
	// 	move_cam_y(1, mt);
	// if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_W))
	// 	move_cam_x(-1, mt);
	// if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_S))
	// 	move_cam_x(1, mt);
	// if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_E))
	// 	move_cam_z(-1, mt);
	// if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_D))
	// 	move_cam_z(1, mt);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_EQUAL))
		zoom(5, mt);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_MINUS))
		zoom(-5, mt);
}
