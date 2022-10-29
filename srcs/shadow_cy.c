#include "minirt.h"

t_vector	get_foot(t_vector coor, t_vector vec, t_vector point)
{
	float		lambda;
	float		divide;
	t_vector	p;

	lambda = (coor.x - point.x) * vec.x;
	lambda += (coor.y - point.y) * vec.y;
	lambda += (coor.z - point.z) * vec.z;
	divide = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	lambda = (lambda / divide) * -1;
	p = vec;
	mult_vec(&p, lambda);
	p = add_vec(coor, p);
	p = sub_vec(point, p);
	normalize_vec(&p);
	return (p);
}

float	p_in_rectangle(t_vector p, t_cylinder *cy, t_vector norm)
{
	t_vector	vec;
	t_vector	a;
	t_vector	b;
	t_vector	c;
	float		r;

	r = cy->diameter / 2 * 1.02;
	vec = cross_prod_vec(cy->orien, norm);
	normalize_vec(&vec);
	c = add_vec(cy->coord, new_vec(cy->orien.x * (cy->height / 2), cy->orien.y
				* (cy->height / 2), cy->orien.z * (cy->height / 2)));
	a = sub_vec(c, new_vec(vec.x * r, vec.y * r, vec.z * r));
	b = sub_vec(a, new_vec(cy->orien.x * (cy->height / 2), cy->orien.y
				* (cy->height / 2), cy->orien.z * (cy->height / 2)));
	a = add_vec(a, new_vec(cy->orien.x * (cy->height / 2), cy->orien.y
				* (cy->height / 2), cy->orien.z * (cy->height / 2)));
	c = add_vec(c, new_vec(vec.x * r, vec.y * r, vec.z * r));
	c = sub_vec(c, new_vec(cy->orien.x * (cy->height / 2), cy->orien.y
				* (cy->height / 2), cy->orien.z * (cy->height / 2)));
	if (scalar_vec(sub_vec(b, p), sub_vec(b, a)) > 0
		&& scalar_vec(sub_vec(b, p), sub_vec(b, a))
		< scalar_vec(sub_vec(b, a), sub_vec(b, a)))
	{
		if (scalar_vec(sub_vec(b, p), sub_vec(b, c)) > 0
			&& scalar_vec(sub_vec(b, p), sub_vec(b, c))
			< scalar_vec(sub_vec(b, c), sub_vec(b, c)))
			return (1);
	}
	return (0);
}

float	shadow_b_inter(t_vector *dot_light, t_vector *ray,
	t_cylinder *cy, t_vector light)
{
	t_plane		pl;
	float		t;
	t_vector	p;

	pl.coord = cy->coord;
	pl.orien = get_foot(cy->coord, cy->orien, light);
	t = shadow_disk_plane_intersect(dot_light, ray, &pl);
	if (ft_comp_float(t, 0) != 0)
	{
		mult_vec(dot_light, t);
		p = add_vec(*ray, *dot_light);
		if ((ft_comp_float(p.x, pl.coord.x) == 0
				&& ft_comp_float(p.y, pl.coord.y) == 0
				&& ft_comp_float(p.z, pl.coord.z) == 0)
			|| (p_in_rectangle(p, cy, pl.orien)))
			return (1);
	}
	return (0);
}

float	shad_cy_intersect(t_vector *dot_light, t_cylinder *cy,
	t_vector *ray, t_vector light)
{
	t_vector	top_disc;
	t_plane		plane;

	if (shadow_b_inter(dot_light, ray, cy, light))
		return (1);
	plane.coord = cy->coord;
	plane.orien = cy->orien;
	plane.color = cy->color;
	if (shadow_disc_intersect(dot_light, ray, &plane, cy->diameter / 2))
		return (1);
	top_disc = cy->orien;
	mult_vec(&top_disc, cy->height);
	plane.coord = add_vec(cy->coord, top_disc);
	plane.orien = cy->orien;
	if (shadow_disc_intersect(dot_light, ray, &plane, cy->diameter / 2))
		return (1);
	return (0);
}

int	shadow_cylinder(t_minirt *mt, t_dist *dist, t_vector *ray)
{
	t_list		*ptr;
	t_cylinder	*cy;

	ptr = mt->obj.cylinder;
	while (ptr)
	{
		cy = ptr->content;
		if (shad_cy_intersect(dist->dot_light, cy, ray, mt->scene.light.coord))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}
