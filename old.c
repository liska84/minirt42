// void    draw_scene(t_minirt *mt)
// {
// 	t_draw		*pic;

// 	pic = malloc(sizeof(t_draw));
// 	pic->mlx_y = 0;
// 	pic->canvas_y = mt->height / 2;
// 	while (pic->canvas_y > (-1 * mt->height / 2))
// 	{
// 		pic->y_ray = pic->canvas_y * mt->vp.y_pix;
// 		pic->canvas_x = -mt->width / 2;
// 		pic->mlx_x = 0;
// 		while (pic->canvas_x < mt->width / 2)
// 		{
// 			pic->x_ray = pic->canvas_x * mt->vp.x_pix;
// 			pic->ray = malloc(sizeof(t_vector));
// 			*pic->ray = new_vec(pic->x_ray, pic->y_ray, mt->scene.camera.direction.z); // mt->scene.camera.direction.z == 1 UNIT
// 			normalize_vec(pic->ray);
// 			draw_objects(mt, pic->ray, &pic->color);
// 			free(pic->ray);
// 			mlx_put_pixel(mt->gr.img, pic->mlx_x, pic->mlx_y, pic->color);
// 			pic->canvas_x++;
// 			pic->mlx_x++;
// 		}
// 		pic->canvas_y--;
// 		pic->mlx_y++;
// 	}
// 	free(pic);
// }

// void    draw_scene(t_minirt *mt)
// {
// 	t_draw		*pic;
// 	t_vector	ray_origin;	
// 	t_vector	p_pix;

// 	pic = malloc(sizeof(t_draw));
// 	pic->mlx_y = 0;
// 	while (pic->mlx_y < mt->height)
// 	{
// 		pic->mlx_x = 0;
// 		while (pic->mlx_x < mt->width)
// 		{
// 			mt->vp.y_pix = (1 - 2.0 * ((pic->mlx_y + 0.5) / mt->height)) * tanf(mt->scene.camera.fov * 0.5 * (M_PI / 180));
// 			mt->vp.x_pix = (2.0 * ((pic->mlx_x + 0.5) / mt->width) - 1) * mt->vp.aspect_ratio * tanf(mt->scene.camera.fov * 0.5 * (M_PI / 180));
// 			// mt->vp.z_pix = - ((mt->vp.height) / tanf(mt->scene.camera.fov * 0.5 * (M_PI / 180))); // or z = -1;

// 			ray_origin = mt->scene.camera.origin;

// 			// the position P of a pixel in the image on the image plane of the camera
// 			p_pix = new_vec(mt->vp.x_pix, mt->vp.y_pix, -1);
			
// 			// Vec3f rayDirection = Vec3f(Px, Py, -1) - rayOrigin
// 			pic->ray = malloc(sizeof(t_vector));
			
// 			*pic->ray = sub_vec(p_pix,ray_origin);
// 			normalize_vec(pic->ray);

// 			draw_objects(mt, pic->ray, &pic->color);
// 			free(pic->ray);
// 			mlx_put_pixel(mt->gr.img, pic->mlx_x, pic->mlx_y, pic->color);
// 			pic->mlx_x++;
// 		}
// 		pic->mlx_y++;
// 	}
// 	free(pic);
// }