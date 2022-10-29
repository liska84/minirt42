#include "minirt.h"

void	draw_pixel(t_minirt *mt, t_draw *pic)
{
	float	x;
	float	y;
	float	z;

	x = pic->mlx_x - mt->width / 2;
	y = mt->height / 2 - pic->mlx_y;
	z = -mt->height
		* 0.5 / tanf(mt->scene.camera.fov * 0.5 * (M_PI / 180));
	pic->x_ray = x * mt->scene.camera.right_u.x + y
		* mt->scene.camera.up_v.x + z * mt->scene.camera.forward_w.x;
	pic->y_ray = x * mt->scene.camera.right_u.y + y
		* mt->scene.camera.up_v.y + z * mt->scene.camera.forward_w.y;
	pic->z_ray = x * mt->scene.camera.right_u.z + y
		* mt->scene.camera.up_v.z + z * mt->scene.camera.forward_w.z;
	pic->ray = malloc(sizeof(t_vector));
	*pic->ray = new_vec(pic->x_ray, pic->y_ray, pic->z_ray);
	normalize_vec(pic->ray);
	draw_objects(mt, pic->ray, &pic->color);
	free(pic->ray);
	mlx_put_pixel(mt->gr.img, pic->mlx_x, pic->mlx_y, pic->color);
}

void	draw_scene(t_minirt *mt)
{
	t_draw	*pic;

	pic = malloc(sizeof(t_draw));
	if (!pic)
		return ;
	pic->mlx_y = 0;
	while (pic->mlx_y < mt->height)
	{
		pic->mlx_x = 0;
		while (pic->mlx_x < mt->width)
		{
			draw_pixel(mt, pic);
			pic->mlx_x++;
		}
		pic->mlx_y++;
	}
	free(pic);
}
