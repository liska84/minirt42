#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include "../includes/libft/libft.h"
# include "../includes/get_next_line/get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../MLX42/include/MLX42/MLX42_Input.h"
# include "../MLX42/include/MLX42/MLX42_Int.h"

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_coef
{
	float	a;
	float	b;
	float	c;
	float	disc;
}	t_coef;

typedef struct s_ambi_light
{
	float	ratio;
	t_color	color;
}	t_ambi_light;

typedef struct s_camera
{
	t_vector	origin;
	t_vector	direction;
	int			fov;
	t_vector	up_v;
	t_vector	right_u;
	t_vector	forward_w;
}	t_camera;

typedef struct s_light
{
	t_vector	coord;
	float		bright;
	t_color		color;
}	t_light;

typedef struct s_sphere
{
	t_vector	center;
	float		diam;
	t_color		color;
}	t_sphere;

typedef struct s_plane
{
	t_vector	coord;
	t_vector	orien;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	t_vector	coord;
	t_vector	orien;
	float		diameter;
	float		height;
	t_color		color;
}	t_cylinder;

typedef struct s_dist
{
	float		dist;
	float		min_dist;
	size_t		closest_obj;
	t_sphere	*cl_sp;
	t_plane		*cl_pl;
	t_cylinder	*cl_cy;
	t_vector	*dot_light;
}	t_dist;

typedef struct s_obj
{
	t_list	*sphere;
	t_list	*plane;
	t_list	*cylinder;
}	t_obj;

typedef struct s_scene
{
	t_ambi_light	a_light;
	t_camera		camera;
	t_light			light;
}	t_scene;

typedef struct s_draw
{
	int			mlx_x;
	int			mlx_y;
	int			color;
	float		x_ray;
	float		y_ray;
	float		z_ray;
	t_vector	*ray;
}	t_draw;

typedef struct s_graphic
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_graphic;

typedef struct s_minirt
{
	t_obj		obj;
	t_scene		scene;
	t_dist		dist;
	t_graphic	gr;
	int32_t		width;
	int32_t		height;
}	t_minirt;

void		error(void);
void		p_error(void);
void		m_error(void);
void		msg_error(char *msg, char **split);
void		leaks(void);

float		ft_stof(char *str);
bool		ft_bit_range(t_color color);
bool		ft_unit_range(t_vector vec);
bool		ft_string_digit(char *str);
void		free_content(void *content);
void		free_list(t_list *head);

void		parser(t_minirt *mt, char *argv);
t_color		parse_color(char **line_split, int i);
t_vector	split_coord(char **str, int i);
t_scene		parse_ambi_light(t_scene scene, char **line_split);
t_scene		parse_camera(t_scene scene, char **line_split);
t_scene		parse_light(t_scene scene, char **line_split);
t_obj		parse_cylinder(t_obj obj, char **line_split);
t_obj		parse_plane(t_obj obj, char **line_split);
t_obj		parse_sphere(t_obj object, char **line_split);

void		calculate_camera(t_minirt *mt);
void		draw_scene(t_minirt *mt);
void		hook(void *param);
void		scrollhook(double xdelta, double ydelta, void *param);
void		resize(int32_t width, int32_t height, void *param);
void		move_cam_y(t_minirt *mt, int y);
void		move_cam_x(t_minirt *mt, int x);
void		move_cam_z(t_minirt *mt, int z);
void		rotate_cam_y(t_minirt *mt, double y);
void		rotate_cam_x(t_minirt *mt, double y);
void		rotate_cam_z(t_minirt *mt, double z);

t_vector	new_vec(float x, float y, float z);
float		len_vec(t_vector v);
void		normalize_vec(t_vector *v);
t_vector	sub_vec(t_vector a, t_vector b);
float		scalar_vec(t_vector a, t_vector b);
void		mult_vec(t_vector *dir, float n);
t_vector	add_vec(t_vector a, t_vector b);
t_vector	cross_prod_vec(t_vector a, t_vector b);

float		sphere_intersect(t_camera cam, t_vector ray, t_sphere *sp);
float		plane_intersect(t_camera cam, t_vector ray, t_plane *pl);
float		cy_intersect(t_minirt *mt,
				t_vector ray, t_dist *dist, t_cylinder *cy);
float		shad_cy_intersect(t_vector *dot_light, t_cylinder *cy,
				t_vector *ray, t_vector light);
bool		compare_caps(float cap, float min_d);

void		closest_sp(t_minirt *mt, t_dist *dist, t_vector *ray);
void		closest_pl(t_minirt *mt, t_dist *dist, t_vector *ray);
void		closest_cy(t_minirt *mt, t_dist *dist, t_vector *ray);

int			draw_pix(t_minirt *mt, t_dist *dist, float int_light);
void		draw_objects(t_minirt *mt, t_vector *ray, int *color);
int			set_color(t_minirt *mt, t_dist *dist, float light);
int			get_rgba(int r, int g, int b, int a);

int			shadow_sphere(t_minirt *mt, t_dist *dist, t_vector *ray);
int			shadow_plane(t_minirt *mt, t_dist *dist, t_vector *ray);
int			shadow_cylinder(t_minirt *mt, t_dist *dist, t_vector *ray);
float		shadow_disc_intersect(t_vector *dot_light,
				t_vector *ray, t_plane *plane, float r);
float		shadow_disk_plane_intersect(t_vector *dot_light,
				t_vector *ray, t_plane *pl);

#endif