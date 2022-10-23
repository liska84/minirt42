#include "minirt.h"

t_vector	new_vec(float x, float y, float z)
{
	t_vector	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

float	len_vec(t_vector v)
{
	float	res;

	res = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	return (res);
}

void	normalize_vec(t_vector *v)
{
	float	length;

	length = len_vec(*v);
	if (length == 0)
	{
		v->x = 1.0;
		return ;
	}
	v->x /= length;
	v->y /= length;
	v->z /= length;
}

t_vector	sub_vec(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

float	scalar_vec(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
