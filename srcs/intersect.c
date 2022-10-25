#include "minirt.h"

float sphere_intersect(t_camera cam, t_vector ray, t_sphere *sp)
{
	t_coef		coef; 
	t_vector	cam_sp;
	float		d1;
	float		d2;

	cam_sp = sub_vec(cam.origin, sp->center);
	coef.a = 1.0;
	coef.b = 2 * scalar_vec(cam_sp, ray);
	coef.c = scalar_vec(cam_sp, cam_sp) - pow(sp->diam / 2, 2);
	coef.disc = pow(coef.b, 2) - 4.0 * coef.a * coef.c;
	if (coef.disc < 0.0)
		return (0);
	d1 = (-1 * coef.b - sqrt(coef.disc)) / 2 * coef.a;
	d2 = (-1 * coef.b + sqrt(coef.disc)) / 2 * coef.a;
	if (d1 > 0.0)
		return (d1);
	else if (d2 > 0.0)
		return (d2);
	return (0.0);
}

float plane_intersect(t_camera cam, t_vector ray, t_plane *pl)
{
	t_vector	d;
	float		pn;
	float		c;
	float		dist;

	c = scalar_vec(pl->orien, ray);
	d = sub_vec(pl->coord, cam.origin);
	if (c)
	{
		pn = scalar_vec(d, pl->orien);
		dist = pn / c;
		if (ft_comp_float(dist, 0) < 0.0)
			return (0.0);
		else
			return (dist);
	}
	else
		return (0.0);
}

void	body_intersect(t_camera cam, t_vector ray, t_cylinder *cy, float *min_d)
{
	t_coef		coef;
	t_vector	cam_cy;
	float		d1;
	float		d2;
	float		m;

	cam_cy = sub_vec(cy->coordinates, cam.origin);
	normalize_vec(&cy->orien);
	coef.a = 1 - pow(scalar_vec(ray, cy->orien), 2);
	coef.b = -2 * (scalar_vec(ray, cam_cy) - (scalar_vec(ray, cy->orien)
				* scalar_vec(cam_cy, cy->orien)));
	coef.c = scalar_vec(cam_cy, cam_cy)
		- pow(scalar_vec(cam_cy, cy->orien), 2)
		- pow(cy->diameter / 2, 2);
	coef.disc = pow(coef.b, 2) - 4.0f * coef.a * coef.c;
	if (ft_comp_float(coef.disc, 0) >= 0.0)
	{
		d1 = (-1 * coef.b - sqrt(coef.disc)) / (2 * coef.a);
		d2 = (-1 * coef.b + sqrt(coef.disc)) / (2 * coef.a);
		m = scalar_vec(ray, cy->orien)
			* d1 - scalar_vec(cam_cy, cy->orien);
		if (ft_comp_float(d1, 0) > 0 && ft_comp_float(m, 0) >= 0
			&& ft_comp_float(m, cy->height) <= 0
			&& ft_comp_float(d1, d2) < 0)
			*min_d = d1;
		m = scalar_vec(ray, cy->orien) * d2
			- scalar_vec(cam_cy, cy->orien);
		if (ft_comp_float(d2, 0) > 0 && ft_comp_float(m, 0) >= 0
			&& ft_comp_float(m, cy->height) <= 0
			&& ft_comp_float(*min_d, 0) < 0)
			*min_d = d2;
	}
}

float	cap_intersect(t_camera cam, t_vector ray, t_plane *pl, float radius)
{
	t_vector	p;
	t_vector	v;
	float		t;
	float		dist;

	t = plane_intersect(cam, ray, pl);
	if (ft_comp_float(t, 0) == 0.0)
		return (0);
	else
	{
		mult_vec(&ray, t);
		p = add_vec(cam.origin, ray);
		v = sub_vec(p, pl->coord);
		dist = sqrt(scalar_vec(v, v));
		if ((ft_comp_float(p.x, pl->coord.x) == 0
				&& ft_comp_float(p.y, pl->coord.y) == 0
				&& ft_comp_float(p.z, pl->coord.z) == 0)
			|| ft_comp_float(dist, radius) <= 0)
			return (t);
	}
	return (0);
}

static void	get_near(t_dist *dist, float min_d, float *d_cap, t_cylinder *cy)
{
	if (min_d < dist->min_dist)
	{
		dist->min_dist = min_d;
		dist->closest_obj = 3;
		if (ft_comp_float(min_d, d_cap[0]) == 0)
			dist->closest_obj = 4;
		if (ft_comp_float(min_d, d_cap[1]) == 0)
			dist->closest_obj = 5;
		dist->cl_cy = cy;
	}
}

float	cy_intersect(t_minirt *mt, t_vector ray, t_dist *dist, t_cylinder *cy)
{
	float		d_cap[2];
	float		min_d;
	t_vector	d2;
	t_plane		pl;

	min_d = INFINITY;
	body_intersect(mt->scene.camera, ray, cy, &min_d);
	pl.coord = cy->coordinates;
	pl.orien = cy->orien;
	pl.color = cy->color;
	d_cap[0] = cap_intersect(mt->scene.camera, ray, &pl, cy->diameter / 2);
	if (ft_comp_float(d_cap[0], 0) > 0
		&& ft_comp_float(d_cap[0], min_d) < 0)
		min_d = d_cap[0];
	d2 = cy->orien;
	mult_vec(&d2, cy->height);
	pl.coord = add_vec(cy->coordinates, d2);
	d_cap[1] = cap_intersect(mt->scene.camera, ray, &pl, cy->diameter / 2);
	if (ft_comp_float(d_cap[1], 0) > 0
		&& ft_comp_float(d_cap[1], min_d) < 0)
		min_d = d_cap[1];
	if (ft_comp_float(min_d, 0) > 0 && min_d != INFINITY)
	{
		get_near(dist, min_d, d_cap, cy);
		return (min_d);
	}
	return (0);
}
