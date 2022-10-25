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

// static int	shad_cy2(t_vector dsph, t_vector lsph, t_cylinder *cy, t_dist *dist)
// {
// 	if (((ft_comp_float(len_vec(dsph), cy->diameter / 2) > 0
// 				&& ft_comp_float(len_vec(lsph), cy->diameter / 2) > 0))
// 		&& (ft_comp_float(scalar_vec(dsph, *dist->dot_light), 0) > 0
// 			&& ft_comp_float(scalar_vec(lsph, *dist->dot_light), 0) < 0))
// 		if ((ft_comp_float(len_vec(cross_prod_vec(dsph, *dist->dot_light))
// 					/ len_vec(*dist->dot_light), cy->diameter / 2) < 0)
// 			|| ft_comp_float(len_vec(cross_prod_vec(dsph, lsph))
// 				/ len_vec(*dist->dot_light), 0) == 0)
// 			return (1);
// 	return (0);
// }

// //Compare with orientation vector, if in direction compare with height, other with diam
// static int	shad_cy1(float len_d_s, float len_l_s, t_cylinder *cy)
// {
// 	if ((ft_comp_float(len_d_s, cy->diameter / 2) < 0
// 			&& ft_comp_float(len_l_s, cy->diameter / 2) > 0)
// 		|| (ft_comp_float(len_d_s, cy->diameter / 2) > 0
// 			&& ft_comp_float(len_l_s, cy->diameter / 2) < 0))
// 		return (1);
// 	return (0);
// }

// float	shadow_b_inter(t_vector *dot_light, t_vector *ray, t_cylinder *cy, t_dist *dist)
// {
// 	t_vector	cyd;
// 	t_vector	cyl;

// 	if (ft_comp_float(dist->closest_obj, 3) != 0
// 			|| (ft_comp_float(dist->closest_obj, 3) == 0
// 				&& (ft_comp_float(cy->coordinates.x, dist->cl_cy->coordinates.x) != 0
// 					&& ft_comp_float(cy->coordinates.y, dist->cl_cy->coordinates.y) != 0
// 					&& ft_comp_float(cy->coordinates.z, dist->cl_cy->coordinates.z) != 0)
// 				&& (ft_comp_float(cy->orien.x, dist->cl_cy->orien.x) != 0
// 					&& ft_comp_float(cy->orien.y, dist->cl_cy->orien.y) != 0
// 					&& ft_comp_float(cy->orien.z, dist->cl_cy->orien.z) != 0)))
// 		{
// 			cyd = sub_vec(*ray, cy->coordinates); //punkt nach mittelpunkt cylinder
// 			cyl = sub_vec(*dot_light, cy->coordinates); //cylinder nach licht
// 			if (shad_cy1(len_vec(cyd), len_vec(cyl), cy))
// 				return (1);
// 			if (shad_cy2(cyd, cyl, cy, dist))
// 				return (1);
// 		}
// 	return (0);
// }

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

t_vector	get_foot(t_vector coor, t_vector vec, t_vector point)
{
	// coor - vec
	float lambda;
	float	divide;
	t_vector p;
	
	//normalize_vec(&vec);
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
	t_vector b;
	t_vector A;
	t_vector B; // Mitte gerade
	t_vector C;
	t_vector D;
	float r;

	r  = cy->diameter / 2 * 1.015;
	b = cross_prod_vec(cy->orien, norm); // in Richtung b diam, in Richtung cy->orien h
	normalize_vec(&b);
	t_vector test = add_vec(cy->coordinates, new_vec(cy->orien.x * (cy->height / 2), cy->orien.y * (cy->height / 2), cy->orien.z * (cy->height / 2)));
	A = sub_vec(test, new_vec(b.x * r, b.y * r, b.z *r));
	B = sub_vec(A, new_vec(cy->orien.x * (cy->height / 2), cy->orien.y * (cy->height / 2), cy->orien.z * (cy->height / 2)));
	A = add_vec(A, new_vec(cy->orien.x * (cy->height / 2), cy->orien.y * (cy->height / 2), cy->orien.z * (cy->height / 2)));
	C = add_vec(test, new_vec(b.x * r, b.y * r, b.z *r));
	D = add_vec(C, new_vec(cy->orien.x * (cy->height / 2), cy->orien.y * (cy->height / 2), cy->orien.z * (cy->height / 2)));
	C = sub_vec(C, new_vec(cy->orien.x * (cy->height / 2), cy->orien.y * (cy->height / 2), cy->orien.z * (cy->height / 2)));
	if (scalar_vec(sub_vec(B, p), sub_vec(B, A)) > 0 && scalar_vec(sub_vec(B, p), sub_vec(B, A)) < scalar_vec(sub_vec(B, A), sub_vec(B, A)))
	{
		if (scalar_vec(sub_vec(B, p), sub_vec(B, C)) > 0 && scalar_vec(sub_vec(B, p), sub_vec(B, C)) < scalar_vec(sub_vec(B, C), sub_vec(B, C)))
		{
			return (1);
			// printf("%f, %f, %f\n", cy->coordinates.x, cy->coordinates.y, cy->coordinates.z);
			// printf("%f, %f, %f\n", A.x, A.y, A.z);
			// printf("%f, %f, %f\n", B.x, B.y, B.z);
			// printf("%f, %f, %f\n", C.x, C.y, C.z);
			// printf("%f, %f, %f\n", D.x, D.y, D.z);
			// printf("%f, %f, %f\n", p.x, p.y, p.z);
			// exit(1);
		}	
	}
	return (0);
}

float	shadow_b_inter(t_vector *dot_light, t_vector *ray, t_cylinder *cy, t_vector light)
{
	// create a new plane
	t_plane pl;
	float t;
	t_vector p;

	pl.coord = cy->coordinates;
	pl.orien = get_foot(cy->coordinates, cy->orien, light);
	// the normal vector is orthogonal to cy->orien and goes through the light
	// cy->coord is plane->coord
	// do normal plane intersect(shadow_disc_plane does not look for intersect)
	t = shadow_disk_plane_intersect(dot_light, ray, &pl);
	// calculate hitpoint (as in shadow_disc)
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
	// is the point in the rectangle? then return 1
}

float	shad_cy_intersect(t_vector *dot_light, t_cylinder *cy, t_vector *ray, t_vector light)
{
	t_vector	top_disc;
	t_plane		plane;

	// if (shadow_b_inter(dot_light, ray, cy, light))
	// {
	// 	//write(1, "shadow\n", 7);
	// 	return (1);
	// }
	(void)light;
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
		// if (shad_body_inter(dist->dot_light, cy, ray))
		// 	return (1);
		if (shad_cy_intersect(dist->dot_light, cy, ray, mt->scene.light.coord))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}
