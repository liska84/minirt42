#include "minirt.h"

static void	dot_normal_cylind(t_dist *dist, t_vector *dot, t_vector *normal)
{
	float		n;
	t_vector	tmp;

	tmp = sub_vec(dist->cl_cy->coord, *dot);
	normalize_vec(&dist->cl_cy->orien);
	n = -scalar_vec(tmp, dist->cl_cy->orien);
	normal->x = -(dist->cl_cy->orien.x * n
			+ dist->cl_cy->coord.x - dot->x);
	normal->y = -(dist->cl_cy->orien.y * n
			+ dist->cl_cy->coord.y - dot->y);
	normal->z = -(dist->cl_cy->orien.z * n
			+ dist->cl_cy->coord.z - dot->z);
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
		*normal = new_vec(dist->cl_pl->orien.x,
				dist->cl_pl->orien.y, dist->cl_pl->orien.z);
	else if (dist->closest_obj == 3)
		dot_normal_cylind(dist, dot, normal);
	else if (dist->closest_obj == 5)
		*normal = new_vec(dist->cl_cy->orien.x,
				dist->cl_cy->orien.y, dist->cl_cy->orien.z);
	else
		*normal = new_vec(dist->cl_cy->orien.x * -1.0,
				dist->cl_cy->orien.y * -1, dist->cl_cy->orien.z * -1);
	normalize_vec(normal);
	int_light = scalar_vec(*dist->dot_light,
			*normal) / (len_vec(*dist->dot_light) * len_vec(*normal));
	free(normal);
	if (ft_comp_float(int_light, 0) < 0)
		int_light = 0.0;
	return (int_light);
}

static t_dist	*dist_init(t_dist *dist)
{
	dist->dist = -INFINITY;
	dist->min_dist = INFINITY;
	dist->closest_obj = 0;
	dist->cl_sp = NULL;
	dist->cl_pl = NULL;
	dist->cl_cy = NULL;
	dist->dot_light = malloc(sizeof(t_vector));
	return (dist);
}

	// else
	// {
	// 	int_light = dot_normal(dist, ray);
	// 	// if (shadow_sphere(mt, dist, ray) || shadow_plane(mt, dist, ray)
	// 	// 	|| shadow_cylinder(mt, dist, ray))
	// 	// 	*color = draw_pix(mt, dist, 0);
	// 	// else
	// 		*color = draw_pix(mt, dist, int_light);
	// }
void	draw_objects(t_minirt *mt, t_vector *ray, int *color)
{
	t_dist	*dist;
	float	int_light;

	int_light = 0;
	dist = malloc(sizeof(t_dist));
	dist = dist_init(dist);
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
		*color = draw_pix(mt, dist, int_light);
	}
	free(dist->dot_light);
	free(dist);
}
