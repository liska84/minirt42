#include "minirt.h"

void	mult_vec(t_vector *dir, float n)
{
	dir->x *= n;
	if (dir->x == -0)
		dir->x = 0;
	dir->y *= n;
	if (dir->y == -0)
		dir->y = 0;
	dir->z *= n;
	if (dir->z == -0)
		dir->z = 0;
}

t_vector	add_vec(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vector	cross_prod_vec(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.y * b.z - a.z * b.y;
	if (res.x == -0)
		res.x = 0;
	res.y = a.z * b.x - a.x * b.z;
	if (res.y == -0)
		res.y = 0;
	res.z = a.x * b.y - a.y * b.x;
	if (res.z == -0)
		res.z = 0;
	return (res);
}
