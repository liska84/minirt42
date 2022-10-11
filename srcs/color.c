#include "minirt.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int	set_color(t_minirt *mt, t_dist *dist, float light)
{
	int		res;
	float	r = 0.0;
	float	g = 0.0;
	float	b = 0.0;
	float	tmp;

	tmp = mt->scene.a_light.color.r * mt->scene.a_light.ratio + light * mt->scene.light.bright * 255.00f;
	if (tmp > 255.0)
		tmp = 255.0;
	if (dist->closest_obj == 1)
		r = dist->cl_sp->color.r * tmp / 255.0;
	else if (dist->closest_obj == 2)
		r = dist->cl_pl->color.r * tmp / 255.0;
	else if (dist->closest_obj >= 3)
		r = dist->cl_cy->color.r * tmp / 255.0;
	tmp = mt->scene.a_light.color.g * mt->scene.a_light.ratio + light * mt->scene.light.bright * 255.00f;
	if (tmp > 255.0)
		tmp = 255.0;
	if (dist->closest_obj == 1)
		g = dist->cl_sp->color.g * tmp / 255.0;
	else if (dist->closest_obj == 2)
		g = dist->cl_pl->color.g * tmp / 255.0;
	else if (dist->closest_obj >= 3)
		g = dist->cl_cy->color.g * tmp / 255.0;
	tmp = mt->scene.a_light.color.b * mt->scene.a_light.ratio + light * mt->scene.light.bright * 255.00f;
	if (tmp > 255.0)
		tmp = 255.0;
	if (dist->closest_obj == 1)
		b = dist->cl_sp->color.b * tmp / 255.0;
	else if (dist->closest_obj == 2)
		b = dist->cl_pl->color.b * tmp / 255.0;
	else if (dist->closest_obj >= 3)
		b = dist->cl_cy->color.b * tmp / 255.0;
	res = get_rgba(r, g, b, 255);
	return(res);
}

int	draw_pix(t_minirt *mt, t_dist *dist, float int_light)
{
	int	res;

	if (dist->closest_obj)
		res = set_color(mt, dist, int_light);
	else
		res = 0xffffe5ff;
	return (res);
}