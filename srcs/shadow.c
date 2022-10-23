#include "minirt.h"

static int	shad_sp2(t_vector *dsph, t_vector *lsph, float r, t_dist *dist)
{
	if (((ft_comp_float(len_vec(*dsph), r) > 0
				&& ft_comp_float(len_vec(*lsph), r) > 0))
		&& (ft_comp_float(scalar_vec(*dsph, *dist->dot_light), 0) > 0
			&& ft_comp_float(scalar_vec(*lsph, *dist->dot_light), 0) < 0))
		if ((ft_comp_float(len_vec(cross_prod_vec(*dsph, *dist->dot_light))
					/ len_vec(*dist->dot_light), r) < 0)
			|| ft_comp_float(len_vec(cross_prod_vec(*dsph, *lsph))
				/ len_vec(*dist->dot_light), 0) == 0)
			return (1);
	return (0);
}

static int	shad_sp1(float len_d_s, float len_l_s, float r)
{
	if ((ft_comp_float(len_d_s, r) < 0
			&& ft_comp_float(len_l_s, r) > 0)
		|| (ft_comp_float(len_d_s, r) > 0
			&& ft_comp_float(len_l_s, r) < 0))
		return (1);
	return (0);
}

int	shadow_sphere(t_minirt *mt, t_dist *dist, t_vector *ray)
{
	t_vector	*dsph;
	t_vector	*lsph;
	t_list		*ptr;
	t_sphere	*sp;

	dsph = malloc(sizeof(t_vector));
	lsph = malloc(sizeof(t_vector));
	ptr = mt->obj.sphere;
	while (ptr)
	{
		sp = ptr->content;
		if (ft_comp_float(dist->closest_obj, 1) != 0
			|| (ft_comp_float(dist->closest_obj, 1) == 0
				&& (ft_comp_float(sp->center.x, dist->cl_sp->center.x) != 0
					&& ft_comp_float(sp->center.y, dist->cl_sp->center.y) != 0
					&& ft_comp_float(sp->center.z, dist->cl_sp->center.z) != 0)
				&& (ft_comp_float(sp->diam, dist->cl_sp->diam) != 0)))
		{
			*dsph = sub_vec(sp->center, *ray);
			*lsph = sub_vec(sp->center, *dist->dot_light);
			if (shad_sp1(len_vec(*dsph), len_vec(*lsph), sp->diam / 2))
			{
				free(dsph);
				free(lsph);
				return (1);
			}
			if (shad_sp2(dsph, lsph, sp->diam / 2, dist))
			{
				free(dsph);
				free(lsph);
				return (1);
			}
		}
		ptr = ptr->next;
	}
	free(dsph);
	free(lsph);
	return (0);
}

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

static float	shadow_disk_plane_intersect(t_vector *dot_light,
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
			return (0);
		return (dist);
	}
	return (0);
}

static float	shadow_disc_intersect(t_vector *dot_light,
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

float	shad_cy_intersect(t_vector *dot_light, t_cylinder *cy, t_vector *ray)
{
	t_vector	top_disc;
	t_plane		plane;

	plane.coord = cy->coordinates;
	plane.orien = cy->orien;
	plane.color = cy->color;
	if (shadow_disc_intersect(dot_light, ray, &plane, cy->diameter / 2))
		return (1);
	top_disc = cy->orien;
	mult_vec(&top_disc, cy->height);
	plane.coord = add_vec(cy->coordinates, top_disc);
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
		if (shad_cy_intersect(dist->dot_light, cy, ray))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}
