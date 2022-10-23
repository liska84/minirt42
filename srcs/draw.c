#include "minirt.h"

static void	closest_sp(t_minirt *mt, t_dist *dist, t_vector *ray)
{
	t_sphere	*sp;
	t_list		*ptr;

	ptr = mt->obj.sphere;
	while (ptr)
	{
		sp = ptr->content;
		dist->dist = sphere_intersect(mt->scene.camera, *ray, sp);
		if (ft_compare_float(dist->dist, 0) > 0
			&& ft_compare_float(dist->dist, dist->min_dist) < 0)
		{
			dist->min_dist = dist->dist;
			dist->closest_obj = 1;
			dist->cl_sp = sp;
		}
		ptr = ptr->next;
	}
}

static void	closest_pl(t_minirt *mt, t_dist *dist, t_vector *ray)
{
	t_plane	*pl;
	t_list	*ptr;

	ptr = mt->obj.plane;
	while (ptr)
	{
		pl = ptr->content;
		dist->dist = plane_intersect(mt->scene.camera, *ray, pl);
		if (ft_compare_float(dist->dist, 0) > 0
			&& ft_compare_float(dist->dist, dist->min_dist) > 0)
		{
			dist->min_dist = dist->dist;
			dist->closest_obj = 2;
			dist->cl_pl = pl;
		}
		ptr = ptr->next;
	}
}

static void	closest_cy(t_minirt *mt, t_dist *dist, t_vector *ray)
{
	t_cylinder	*cy;
	t_list		*ptr;

	ptr = mt->obj.cylinder;
	while (ptr)
	{
		cy = ptr->content;
		dist->dist = cy_intersect(mt, *ray, dist, cy);
		ptr = ptr->next;
	}
}

static void	dot_normal_cylind(t_dist *dist, t_vector *dot, t_vector *normal)
{
	float		n;
	t_vector	tmp;

	tmp = sub_vec(dist->cl_cy->coordinates, *dot);
	normalize_vec(&dist->cl_cy->orientation);
	n = -scalar_vec(tmp, dist->cl_cy->orientation);
	normal->x = -(dist->cl_cy->orientation.x * n
			+ dist->cl_cy->coordinates.x - dot->x);
	normal->y = -(dist->cl_cy->orientation.y * n
			+ dist->cl_cy->coordinates.y - dot->y);
	normal->z = -(dist->cl_cy->orientation.z * n
			+ dist->cl_cy->coordinates.z - dot->z);
	normalize_vec(normal);
	normalize_vec(dist->dot_light);
}

static float	dot_normal(t_dist *dist, t_vector *dot)
{
	t_vector	*normal;
	float		int_light;

	normal = malloc(sizeof(t_vector));
	if (dist->closest_obj == 1)
		*normal = sub_vec(*dot, dist->cl_sp->center);
	else if (dist->closest_obj == 2)
		*normal = new_vec(dist->cl_pl->orientation.x,
				dist->cl_pl->orientation.y, dist->cl_pl->orientation.z);
	else if (dist->closest_obj == 3)
		dot_normal_cylind(dist, dot, normal);
	else if (dist->closest_obj == 5)
		*normal = new_vec(dist->cl_cy->orientation.x,
				dist->cl_cy->orientation.y, dist->cl_cy->orientation.z);
	else
		*normal = new_vec(dist->cl_cy->orientation.x * -1.0, dist->cl_cy->orientation.y * -1.0, dist->cl_cy->orientation.z * -1.0);
	normalize_vec(normal);
	int_light = scalar_vec(*dist->dot_light,
			*normal) / (len_vec(*dist->dot_light) * len_vec(*normal));
	free(normal);
	if (ft_compare_float(int_light, 0) < 0)
		int_light = 0.0;
	return (int_light);
}

static void	draw_objects(t_minirt *mt, t_vector *ray, int *color)
{
	t_dist	*dist;
	float	int_light;

	int_light = 0;
	dist = malloc(sizeof(t_dist));
	dist->dist = -INFINITY;
	dist->min_dist = INFINITY;
	dist->closest_obj = 0;
	dist->cl_sp = NULL;
	dist->cl_pl = NULL;
	dist->cl_cy = NULL;
	dist->dot_light = malloc(sizeof(t_vector));
	closest_sp(mt, dist, ray);
	closest_pl(mt, dist, ray);
	closest_cy(mt, dist, ray);
	mult_vec(ray, dist->min_dist);
	*ray = add_vec(*ray, mt->scene.camera.origin);
	*dist->dot_light = sub_vec(mt->scene.light.coord, *ray);
	if (!dist->closest_obj)
		*color = 0xffffe5ff;
	else
	{
		int_light = dot_normal(dist, ray);
		if (shadow_sphere(mt, dist, ray) || shadow_plane(mt, dist, ray)
			|| shadow_cylinder(mt, dist, ray))
			*color = draw_pix(mt, dist, 0);
		else
			*color = draw_pix(mt, dist, int_light);
	}
	free(dist->dot_light);
	free(dist);
}

void	draw_scene(t_minirt *mt)
{
	t_draw	*pic;
	float	x;
	float	y;
	float	z;

	pic = malloc(sizeof(t_draw));
	if (!pic)
		return ;
	pic->mlx_y = 0;
	while (pic->mlx_y < mt->height)
	{
		pic->mlx_x = 0;
		while (pic->mlx_x < mt->width)
		{
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
			pic->mlx_x++;
		}
		pic->mlx_y++;
	}
	free(pic);
}
