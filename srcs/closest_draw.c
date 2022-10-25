#include "minirt.h"

void	closest_sp(t_minirt *mt, t_dist *dist, t_vector *ray)
{
	t_sphere	*sp;
	t_list		*ptr;

	ptr = mt->obj.sphere;
	while (ptr)
	{
		sp = ptr->content;
		dist->dist = sphere_intersect(mt->scene.camera, *ray, sp);
		if (dist->dist > 0 && dist->dist < dist->min_dist)
		{
			dist->min_dist = dist->dist;
			dist->closest_obj = 1;
			dist->cl_sp = sp;
		}
		ptr = ptr->next;
	}
}

void	closest_pl(t_minirt *mt, t_dist *dist, t_vector *ray)
{
	t_plane	*pl;
	t_list	*ptr;

	ptr = mt->obj.plane;
	while (ptr)
	{
		pl = ptr->content;
		dist->dist = plane_intersect(mt->scene.camera, *ray, pl);
		if (dist->dist > 0 && dist->dist < dist->min_dist)
		{
			dist->min_dist = dist->dist;
			dist->closest_obj = 2;
			dist->cl_pl = pl;
		}
		ptr = ptr->next;
	}
}

void	closest_cy(t_minirt *mt, t_dist *dist, t_vector *ray)
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
