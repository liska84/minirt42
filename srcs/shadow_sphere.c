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
