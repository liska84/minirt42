#include "minirt.h"

float	sphere_intersect(t_camera cam, t_vector ray, t_sphere *sp)
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

float	plane_intersect(t_camera cam, t_vector ray, t_plane *pl)
{
	t_vector	d;
	float		pn;
	float		c;
	float		dist;

	if (scalar_vec(ray, pl->orien) == 0)
		return (0);
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
