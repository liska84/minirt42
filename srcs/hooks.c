#include "minirt.h"

static void move_cam_x(int x_axis, t_minirt *mt)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
	t_list		*ptr = NULL;
	int x = x_axis * 5;

	if (mt->obj.sphere)
	{
		ptr = mt->obj.sphere;
		while (ptr)
		{
			sp = ptr->content;
			sp->center.x -= x; 
			ptr = ptr->next;
		}
	}
	if (mt->obj.plane)
	{
		ptr = mt->obj.plane;
		while (ptr)
		{
			pl = ptr->content;
			pl->coord.x -= x;
			ptr = ptr->next;
		}
	}
	if (mt->obj.cylinder)
	{
		ptr = mt->obj.cylinder;
		while (ptr)
		{
			cy = ptr->content;
			cy->coordinates.x -= x;
			ptr = ptr->next;
		}	
	}
	draw_scene(mt);
}

static void move_cam_y(int y_axis, t_minirt *mt)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
	t_list		*ptr = NULL;
	int y = y_axis * 5;

	if (mt->obj.sphere)
	{
		ptr = mt->obj.sphere;
		while (ptr)
		{
			sp = ptr->content;
			sp->center.y -= y; 
			ptr = ptr->next;
		}
	}
	if (mt->obj.plane)
	{
		ptr = mt->obj.plane;
		while (ptr)
		{
			pl = ptr->content;
			pl->coord.y -= y;
			ptr = ptr->next;
		}
	}
	if (mt->obj.cylinder)
	{
		ptr = mt->obj.cylinder;
		while (ptr)
		{
			cy = ptr->content;
			cy->coordinates.y -= y;
			ptr = ptr->next;
		}	
	}
	draw_scene(mt);
}

static void move_cam_z(int z_axis, t_minirt *mt)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
	t_list		*ptr = NULL;
	int z = z_axis * 5;

	if (mt->obj.sphere)
	{
		ptr = mt->obj.sphere;
		while (ptr)
		{
			sp = ptr->content;
			sp->center.z += z; 
			ptr = ptr->next;
		}
	}
	if (mt->obj.plane)
	{
		ptr = mt->obj.plane;
		while (ptr)
		{
			pl = ptr->content;
			pl->coord.z += z;
			ptr = ptr->next;
		}
	}
	if (mt->obj.cylinder)
	{
		ptr = mt->obj.cylinder;
		while (ptr)
		{
			cy = ptr->content;
			cy->coordinates.z += z;
			ptr = ptr->next;
		}	
	}
	draw_scene(mt);
}

void resize(int32_t width, int32_t height, void* param)
{
	t_minirt *mt;

	mt = param;
	mt->height = height;
	mt->width = width;
	draw_scene(mt);
}

void	hook(void *param)
{
	t_minirt *mt;

	mt = param;

	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_ESCAPE)) // Add red cross
		mlx_close_window(mt->gr.mlx);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_Q))
		move_cam_y(-1, mt);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_A))
		move_cam_y(1, mt);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_W))
		move_cam_x(-1, mt);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_S))
		move_cam_x(1, mt);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_E))
		move_cam_z(-1, mt);
	if (mlx_is_key_down(mt->gr.mlx, MLX_KEY_D))
		move_cam_z(1, mt);
}
