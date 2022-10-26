#include "minirt.h"

int	shadow_plane(t_minirt *mt, t_dist *dist, t_vector *ray)
{
	t_list		*ptr;
	t_plane		*pl;
	t_vector	pld;
	t_vector	pll;

	ptr = mt->obj.plane;
	while (ptr)
	{
		pl = ptr->content;
		if (ft_comp_float(dist->closest_obj, 2) != 0
			|| (ft_comp_float(dist->closest_obj, 2) == 0
				&& (ft_comp_float(pl->coord.x, dist->cl_pl->coord.x) != 0
					&& ft_comp_float(pl->coord.y, dist->cl_pl->coord.y) != 0
					&& ft_comp_float(pl->coord.z, dist->cl_pl->coord.z) != 0)
				&& (ft_comp_float(pl->orien.x, dist->cl_pl->orien.x) != 0
					&& ft_comp_float(pl->orien.y, dist->cl_pl->orien.y) != 0
					&& ft_comp_float(pl->orien.z, dist->cl_pl->orien.z) != 0)))
		{
			pld = sub_vec(*ray, pl->coord);
			pll = sub_vec(mt->scene.light.coord, pl->coord);
			if ((scalar_vec(pld, pl->orien) > 0
					&& scalar_vec(pll, pl->orien) < 0)
				|| (scalar_vec(pld, pl->orien) < 0
					&& scalar_vec(pll, pl->orien) > 0))
				return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

float	shadow_disk_plane_intersect(t_vector *dot_light,
		t_vector *ray, t_plane *pl)
{
	t_vector	d;
	float		pn;
	float		c;
	float		dist;

	c = scalar_vec(pl->orien, *dot_light);
	d = sub_vec(pl->coord, *ray);
	if (ft_comp_float(c, 0) != 0)
	{
		pn = scalar_vec(d, pl->orien);
		dist = pn / c;
		if (ft_comp_float(dist, 0) < 0)
			return (0.0);
		return (dist);
	}
	return (0.0);
}

float	shadow_disc_intersect(t_vector *dot_light,
		t_vector *ray, t_plane *plane, float r)
{
	t_vector	p;
	t_vector	v;
	float		t;
	float		dist;

	t = shadow_disk_plane_intersect(dot_light, ray, plane);
	if (ft_comp_float(t, 0) != 0)
	{
		mult_vec(dot_light, t);
		p = add_vec(*ray, *dot_light);
		v = sub_vec(p, plane->coord);
		dist = sqrtf(scalar_vec(v, v));
		if ((ft_comp_float(p.x, plane->coord.x) == 0
				&& ft_comp_float(p.y, plane->coord.y) == 0
				&& ft_comp_float(p.z, plane->coord.z) == 0)
			|| ft_comp_float(dist, r) <= 0)
			return (1);
	}
	return (0);
}
