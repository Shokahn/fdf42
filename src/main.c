/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:13:15 by stdevis           #+#    #+#             */
/*   Updated: 2025/03/01 16:10:18 by stdevis          ###   ########.fr       */
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
	//mlx_destroy_display(var->mlx_p);
	ft_free_error("end of the programme\n", 0, var);
	exit(0);
}

void	scaling_down(t_fdf *var)
{
	int x;
	int y;

	y = 0;
	clear_image(var);
	while(y < var->map->height)
	{
		x = 0;
		while( x < var->map->width)
		{
			if (var->map->coord[y][x].true_zero == 0)
				var->map->coord[y][x].z -= SCALING;
			x++;	
		}
		y++;
	}
	if (var->map->max_z != 0)
		var->map->max_z -= SCALING;
	if (var->map->min_z != 0)
		var->map->min_z -= SCALING;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	printf("max_z = %f, min_z = %f\n", var->map->max_z, var->map->min_z);
}

void	scaling_up(t_fdf *var)
{
	int x;
	int y;

	y = 0;
	clear_image(var);
	while(y < var->map->height)
	{
		x = 0;
		while( x < var->map->width)
		{
			if (var->map->coord[y][x].true_zero == 0)
				var->map->coord[y][x].z += SCALING;
			x++;	
		}
		y++;
	}
	if (var->map->max_z != 0)
		var->map->max_z += SCALING;
	if (var->map->min_z != 0)
		var->map->min_z += SCALING;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	printf("max_z = %f, min_z = %f\n", var->map->max_z, var->map->min_z);
}

void	reset(t_fdf *var)
{
	clear_image(var);
	var->map->radius = RADIUS_Z;
	var->img->distance = DISTANCE;
	var->map->p = 0;
	var->img->x = 0;
	var->img->y = 0;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_printf("Hard reset\n");
}

void	projection_change(t_fdf *var)
{
	var->map->p++;
	if (var->map->p > 4)
		var->map->p = 0;
	clear_image(var);
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_printf("Projection change\n");
}

void	reset_without_projection(t_fdf *var)
{
	clear_image(var);
	var->map->radius = RADIUS_Z;
	var->img->distance = DISTANCE;
	var->img->x = 0;
	var->img->y = 0;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_printf("Soft reset\n");
}

int	key_hook(int keycode, t_fdf *var)
{
	if (keycode == 53)
		closer(var);
	if (keycode == 126)
		going_up(var);
	if (keycode == 125)
		going_down(var);
	if (keycode == 123)
		going_left(var);
	if (keycode == 124)
		going_right(var);
	if (keycode == 13)
		scaling_up(var);
	if (keycode == 1)
		scaling_down(var);
	if (keycode == 15)
		reset(var);
	if (keycode == 35)
		projection_change(var);
	if (keycode == 17)
		reset_without_projection(var);
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
		//mlx_destroy_display(var->mlx_p);
		ft_free_error("destroy wind failed\n", 0, var);
	}
	var->img->img_p = mlx_new_image(var->mlx_p, WIGHT, HEIGHT);
}

void	wind_destruction(t_fdf *var)
{
	mlx_destroy_image(var->mlx_p, var->img->img_p);
	mlx_destroy_window(var->mlx_p, var->win_p);
	//mlx_destroy_display(var->mlx_p);
	free(var->mlx_p);
	free_fdf(var);
}

void	put_pixel(t_image *img, int x_d, int y_d, t_map *map)
{
	int	index;
	int	x_sized;
	int	y_sized;

	(void)map;
	x_sized = x_d + (WIGHT / 2);
	y_sized = y_d + (HEIGHT / 4);
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
			+ index) = map->coord[map->y_index][map->x_index].color;
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

void	dimetric_transform(float *x, float *y, float z)
{
	int		old_x;
	int		old_y;
	float	alpha;
	float	beta;

	old_x = *x;
	old_y = *y;
	alpha = 42.0 * M_PI / 180.0;
	beta = 7.0 * M_PI / 180.0;
	*x = old_x * cos(alpha) - old_y * cos(beta);
	*y = old_x * sin(alpha) + old_y * sin(beta) - z;
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

	tmp = point_init(var->map->x_d, var->map->y_d, var->map->z_d, COLOR);
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
		dimetric_transform(x, y, z);
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

	next = point_init(0, 0, 0, COLOR);
	tmp = point_init(map->x_d, map->y_d, map->z_d, COLOR);
	if (map->x_index == 0 && map->y_index == 0)
		map->coord[map->y_index][map->x_index].color = 0xFF0000;
	chose_projection(var, &map->x_d, &map->y_d, map->z_d);
	put_pixel(var->img, (int)map->x_d, (int)map->y_d, map);
	if (map->x_index < map->width - 1)
	{
		next->x = tmp->x + var->img->distance;
		next->y = tmp->y;
		next->z = map->coord[map->y_index][map->x_index + 1].z
			* (var->img->distance * map->radius);
		chose_projection(var, &next->x, &next->y, next->z);
		draw_line(var, next);
	}
	if (map->y_index < map->height - 1)
	{
		next->x = tmp->x;
		next->y = tmp->y + var->img->distance;
		next->z = map->coord[map->y_index + 1][map->x_index].z
			* (var->img->distance * map->radius);
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
	ft_printf("Zoomed in for %d pixels\n", ZOOM);
}

void	zoom_out(t_fdf *var)
{
	if (var->img->distance - ZOOM > 0)
	{
		clear_image(var);
		var->img->distance -= ZOOM;
		put_the_grid(var, var->map);
		mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
		ft_printf("Zoomed out for %d pixels\n", ZOOM);
	}
	else
		ft_printf("Maximum size of dezoom reached\n");
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
