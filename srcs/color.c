#include "minirt.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static int	get_r_value(t_minirt *mt, t_dist *dist, float light)
{
	float	r;
	float	tmp;

	r = 0.0;
	tmp = mt->scene.a_light.color.r * mt->scene.a_light.ratio
		+ light * mt->scene.light.bright * 255.00f;
	if (ft_comp_float(tmp, 255.0) > 0)
		tmp = 255.0;
	if (dist->closest_obj == 1)
		r = dist->cl_sp->color.r * tmp / 255.0;
	else if (dist->closest_obj == 2)
		r = dist->cl_pl->color.r * tmp / 255.0;
	else if (dist->closest_obj >= 3)
		r = dist->cl_cy->color.r * tmp / 255.0;
	return (r);
}

static int	get_g_value(t_minirt *mt, t_dist *dist, float light)
{
	float	g;
	float	tmp;

	g = 0.0;
	tmp = mt->scene.a_light.color.g * mt->scene.a_light.ratio
		+ light * mt->scene.light.bright * 255.00f;
	if (ft_comp_float(tmp, 255.0) > 0)
		tmp = 255.0;
	if (dist->closest_obj == 1)
		g = dist->cl_sp->color.g * tmp / 255.0;
	else if (dist->closest_obj == 2)
		g = dist->cl_pl->color.g * tmp / 255.0;
	else if (dist->closest_obj >= 3)
		g = dist->cl_cy->color.g * tmp / 255.0;
	return (g);
}

int	set_color(t_minirt *mt, t_dist *dist, float light)
{
	int		res;
	float	r;
	float	g;
	float	b;
	float	tmp;

	b = 0.0;
	r = get_r_value(mt, dist, light);
	g = get_g_value(mt, dist, light);
	tmp = mt->scene.a_light.color.b * mt->scene.a_light.ratio
		+ light * mt->scene.light.bright * 255.00f;
	if (ft_comp_float(tmp, 255.0) > 0)
		tmp = 255.0;
	if (dist->closest_obj == 1)
		b = dist->cl_sp->color.b * tmp / 255.0;
	else if (dist->closest_obj == 2)
		b = dist->cl_pl->color.b * tmp / 255.0;
	else if (dist->closest_obj >= 3)
		b = dist->cl_cy->color.b * tmp / 255.0;
	res = get_rgba(r, g, b, 255);
	return (res);
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
