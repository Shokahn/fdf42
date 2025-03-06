/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shokahn <shokahn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:13:15 by stdevis           #+#    #+#             */
/*   Updated: 2025/03/06 15:07:03 by shokahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	ft_swap_float(float *x, float *y)
{
	float	*tmp;

	tmp = x;
	x = y;
	y = tmp;
}

void	ft_draw_instructions(t_fdf *var)
{
	mlx_string_put(var->mlx_p, var->win_p, 10, 10, 0xFFFFFF,
		"Molette : Zoom");
	mlx_string_put(var->mlx_p, var->win_p, 10, 30, 0xFFFFFF,
		"1 or 3  : ROTATE X");
	mlx_string_put(var->mlx_p, var->win_p, 10, 50, 0xFFFFFF,
		"4 or 6  : ROTATE Y");
	mlx_string_put(var->mlx_p, var->win_p, 10, 70, 0xFFFFFF,
		"7 or 9  : ROTATE Z");
	mlx_string_put(var->mlx_p, var->win_p, 10, 90, 0xFFFFFF,
		" Arrow  : Translate");
	mlx_string_put(var->mlx_p, var->win_p, 10, 110, 0xFFFFFF,
		"   R    : Reset");
	mlx_string_put(var->mlx_p, var->win_p, 10, 130, 0xFFFFFF,
		"   T    : Soft reset");
	mlx_string_put(var->mlx_p, var->win_p, 10, 150, 0xFFFFFF,
		"   P    : Change projection");
	mlx_string_put(var->mlx_p, var->win_p, 10, 170, 0xFFFFFF,
		"W or S  : Scaling");

}

void	clear_image(t_fdf *var)
{
	int	img_size;

	img_size = HEIGHT * WIGHT * 4;
	ft_memset(var->img->addr, 0, img_size);
}

int	closer(t_fdf *var)
{
	ft_printf("the ESC key or red cross has been pressed\n");
	mlx_destroy_image(var->mlx_p, var->img->img_p);
	mlx_destroy_window(var->mlx_p, var->win_p);
	mlx_destroy_display(var->mlx_p);
	ft_free_error("end of the programme\n", 0, var);
	exit(0);
}

void	scaling_down(t_fdf *var)
{
	clear_image(var);
	var->map->radius -= RADIUS_SCALE;

	if (var->map->max_z < var->map->min_z)
		ft_swap_float(&var->map->max_z, &var->map->min_z);
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}

void	scaling_up(t_fdf *var)
{
	clear_image(var);
	var->map->radius += RADIUS_SCALE;
	if (var->map->max_z < var->map->min_z)
		ft_swap_float(&var->map->max_z, &var->map->min_z);
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}

void	reset(t_fdf *var)
{
	clear_image(var);
	var->map->radius = RADIUS_Z;
	calculate_distance(var);
	var->map->p = 0;
	var->img->x = 0;
	var->img->y = 0;
	var->img->rotation_x = 0;
	var->img->rotation_y = 0;
	var->img->rotation_z = 0;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}

void	projection_change(t_fdf *var)
{
	var->map->p++;
	if (var->map->p > 4)
		var->map->p = 0;
	clear_image(var);
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}

void	reset_without_projection(t_fdf *var)
{
	clear_image(var);
	var->map->radius = RADIUS_Z;
	calculate_distance(var);
	var->img->x = 0;
	var->img->y = 0;
	var->img->rotation_x = 0;
	var->img->rotation_y = 0;
	var->img->rotation_z = 0;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}

void	change_color(t_fdf *var)
{
	clear_image(var);
	var->map->color_check++;
	if (var->map->color_check > 4)
		var->map->color_check = 0;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}

int	key_hook(int keycode, t_fdf *var)
{
	if (keycode == XK_Escape)
		closer(var);
	if (keycode == XK_Up || keycode == XK_Down || keycode == XK_Left
		|| keycode == XK_Right)
		translate(keycode, var);
	if (keycode == XK_w)
		scaling_up(var);
	if (keycode == XK_s)
		scaling_down(var);
	if (keycode == XK_r)
		reset(var);
	if (keycode == XK_p)
		projection_change(var);
	if (keycode == XK_t)
		reset_without_projection(var);
	if (keycode == XK_1 || keycode == XK_3 || keycode == XK_4 
		|| keycode == XK_6 || keycode == XK_7 || keycode == XK_9)
		rotate(keycode, var);
	if (keycode == XK_space)
		change_color(var);
	return (0);
}

void	wind_init(t_fdf *var)
{
	if (!var)
		exit(1);
	var->mlx_p = mlx_init();
	if (!var->mlx_p)
	{
		free_fdf(var);
		exit(1);
	}
	var->win_p = mlx_new_window(var->mlx_p, WIGHT, HEIGHT, "fdf");
	if (!var->win_p)
	{
		mlx_destroy_display(var->mlx_p);
		ft_free_error("destroy wind failed\n", 0, var);
	}
	var->img->img_p = mlx_new_image(var->mlx_p, WIGHT, HEIGHT);
}

void	wind_destruction(t_fdf *var)
{
	mlx_destroy_image(var->mlx_p, var->img->img_p);
	mlx_destroy_window(var->mlx_p, var->win_p);
	mlx_destroy_display(var->mlx_p);
	free(var->mlx_p);
	free_fdf(var);
}

int rgb_color(int color1, int color2, float ratio)
{
	int	r1;
	int	g1;
	int	b1;
	int	r;
	int	g;

	r1 = (color1 >> 16) & 0xFF;
	g1 = (color1 >> 8) & 0xFF;
	b1 = color1 & 0xFF;
	r = (int)(r1 + ((color2 >> 16) & (0xFF - r1)) * ratio);
	g = (int)(g1 + ((color2 >> 8) & (0xFF - g1)) * ratio);
	b1 = (color1 & 0xFF) + ((color2 & (0xFF - b1)) * ratio);
	return ((r << 16) | (g << 8) | b1);
}

void	get_color_start_end(t_map *map, int *color_start, int *color_end)
{
	if (map->color_check == 0)
	{
		*color_start = 0x373B44;
		*color_end =  0x4286f4;
	}
	if (map->color_check == 4)
	{
		*color_start = 0x159957;
		*color_end = 0x155799;
	}
	if (map->color_check == 2)
	{
		*color_start = 0x202020;
		*color_end = 0x0f9b0f;
	}
	if (map->color_check == 3)
	{
		*color_start = 0x616161;
		*color_end = 0x9bc5c3;
	}
	if (map->color_check == 1)
	{
		*color_start = 0x1D4350;
		*color_end = 0xA43931;
	}
}

int		get_color(t_map *map)
{
	int 	color_start;
	int 	color_end;
	float   true_z;
	float	percent;

	true_z = fabs(map->true_z);
	percent = (true_z - (map->min_z)) 
			/ ((map->max_z) - (map->min_z));
	if (percent < 0)
		percent = 0;
	if (percent > 1)
		percent = 1;
	if (percent < 0)
		percent = 1;
	get_color_start_end(map, &color_start, &color_end);
	
	return (rgb_color(color_start, color_end, percent));
}

void	put_pixel(t_image *img, int x_d, int y_d, t_map *map)
{
	int	index;
	int	x_sized;
	int	y_sized;

	x_sized = x_d + img->offset_x;
	y_sized = y_d + img->offset_y;
	if (img->x == 0 && img->y == 0)
	{
		if (x_sized <= 0 || x_sized >= WIGHT || y_sized <= 0
			|| y_sized >= HEIGHT)
			return ;
	}
	if (x_sized + img->x <= 0 || x_sized + img->x >= WIGHT || y_sized
		+ img->y <= 0 || y_sized + img->y >= HEIGHT)
		return ;
	index = (((y_sized + img->y) * img->line_lenght)) + (((x_sized + img->x)
				* (img->bpp / 8)));
	*(unsigned int *)(img->addr
			+ index) = get_color(map);
}

void	isometric_transform(float *x, float *y, float z)
{
	int	old_x;
	int	old_y;

	old_x = *x;
	old_y = *y;
	*x = (old_x - old_y) * cos(M_PI / 6);     // cos(30°)
	*y = (old_x + old_y) * sin(M_PI / 6) - z; // sin(30°) - z
}

void	perspective_transform(float *x, float *y, float z, t_fdf *var)
{
	float d;

	d = (var->map->width * var->img->distance) * 5;
    if (z / d < -1)
        return;

    float factor = 1 / (1 + z / d);
    *x = *x * factor;
    *y = *y * factor;
}

void	draw_lineH(int dx, int dy, t_fdf *var, t_coord *tmp)
{
	int	p;
	int	i;
	int	step_x;
	int	step_y;

	step_x = 1;
	step_y = 1;
	if (dx < 0)
		step_x = -1;
	if (dy < 0)
		step_y = -1;
	p = 2 * abs(dy) - abs(dx);
	i = 0;
	while (i <= abs(dx))
	{
		put_pixel(var->img, tmp->x, tmp->y, var->map);
		tmp->x += step_x;
		if (p >= 0)
		{
			tmp->y += step_y;
			p -= 2 * abs(dx);
		}
		p += 2 * abs(dy);
		i++;
	}
}

void	draw_lineV(int dx, int dy, t_fdf *var, t_coord *tmp)
{
	int	p;
	int	i;
	int	step_x;
	int	step_y;

	step_x = 1;
	step_y = 1;
	if (dx < 0)
		step_x = -1;
	if (dy < 0)
		step_y = -1;
	p = 2 * abs(dx) - abs(dy);
	i = 0;
	while (i <= abs(dy))
	{
		put_pixel(var->img, tmp->x, tmp->y, var->map);
		tmp->y += step_y;
		if (p >= 0)
		{
			tmp->x += step_x;
			p -= 2 * abs(dy);
		}
		p += 2 * abs(dx);
		i++;
	}
}

void	draw_line(t_fdf *var, t_coord *next)
{
	int		dx;
	int		dy;
	t_coord	*tmp;

	tmp = point_init(var->map->x_d, var->map->y_d, var->map->z_d, 0);
	dx = (int)next->x - (int)var->map->x_d;
	dy = (int)next->y - (int)var->map->y_d;
	if (abs(dx) > abs(dy))
		draw_lineH(dx, dy, var, tmp);
	else
		draw_lineV(dx, dy, var, tmp);
	free(tmp);
}

void	chose_projection(t_fdf *var, float *x, float *y, float z)
{
	if (var->map->p == 0)
		isometric_transform(x, y, z);
	if (var->map->p == 1)
		perspective_transform(x, y, z, var);
	if (var->map->p == 2)
		*y = -z;
	if (var->map->p == 3)
	{
		*x = *y;
		*y = -z;
	}
}

void	make_the_map(t_fdf *var, t_map *map)
{
	t_coord	*next;
	t_coord	*tmp;

	next = point_init(0, 0, 0, 0);
	tmp = point_init(map->x_d, map->y_d, map->z_d, 0);
	applicate_rotation(var, &map->x_d, &map->y_d, &map->z_d);
	chose_projection(var, &map->x_d, &map->y_d, map->z_d);
	put_pixel(var->img, (int)map->x_d, (int)map->y_d, map);
	if (map->x_index < map->width - 1)
	{
		next->x = tmp->x + var->img->distance;
		next->y = tmp->y;
		next->z = map->coord[map->y_index][map->x_index + 1].z
			* (var->img->distance * map->radius);
		applicate_rotation(var, &next->x, &next->y, &next->z);
		chose_projection(var, &next->x, &next->y, next->z);
		draw_line(var, next);
	}
	if (map->y_index < map->height - 1)
	{
		next->x = tmp->x;
		next->y = tmp->y + var->img->distance;
		next->z = map->coord[map->y_index + 1][map->x_index].z
			* (var->img->distance * map->radius);
		applicate_rotation(var, &next->x, &next->y, &next->z);
		chose_projection(var, &next->x, &next->y, next->z);
		draw_line(var, next);
	}
	free(next);
	free(tmp);
}

void	put_the_grid(t_fdf *var, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->x_d = x * var->img->distance;
			map->y_d = y * var->img->distance;
			map->z_d = map->coord[y][x].z * (var->img->distance * map->radius);
			map->x_index = x;
			map->y_index = y;
			map->true_z = map->coord[y][x].z * map->radius;
			make_the_map(var, map);
			x++;
		}
		y++;
	}
}

void	zoom_in(t_fdf *var)
{
	clear_image(var);
	var->img->distance += ZOOM;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}

void	zoom_out(t_fdf *var)
{
	if (var->img->distance - ZOOM <= 0)
		return ;
	clear_image(var);
	var->img->distance -= ZOOM;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}

int	mouse_hook(int keycode, int x, int y, t_fdf *var)
{
	(void)x;
	(void)y;
	if (keycode == 4)
		zoom_in(var);
	if (keycode == 5)
		zoom_out(var);
	return (0);
}

void	resolve_image(t_fdf *var)
{
	var->img->addr = mlx_get_data_addr(var->img->img_p, &var->img->bpp,
			&var->img->line_lenght, &var->img->endian);
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
	mlx_hook(var->win_p, 2, 1L << 0, key_hook, var);
	mlx_hook(var->win_p, 17, 0, closer, var);
	mlx_mouse_hook(var->win_p, mouse_hook, var);
	mlx_loop(var->mlx_p);
}

int	main(int ac, char **av)
{
	t_fdf	*var;

	if (ac == 2)
	{
		initialization(&var);
		map_read(var, av[1]);
		wind_init(var);
		resolve_image(var);
		wind_destruction(var);
	}
	else
	{
		ft_putstr_fd(BOLD RED "Error : numbers of arguments\n" RESET, 2);
		ft_putstr_fd(ITALIC "Usage: ./fdf \"map.fdf\"\n" RESET, 1);
		return (1);
	}
	return (0);
}
