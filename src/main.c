/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:13:15 by stdevis           #+#    #+#             */
/*   Updated: 2025/02/26 19:41:22 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	clear_image(t_fdf *var)
{
	int	img_size;

	img_size = HEIGHT * WIGHT * 4;
	ft_memset(var->img->addr, 0, img_size);
}

void	closer(t_fdf *var, int keycode)
{
	ft_printf("the %d key (ESC) has been pressed\n", keycode);
	ft_printf("end of the programme\n\n");
	mlx_destroy_image(var->mlx_p, var->img->img_p);
	mlx_destroy_window(var->mlx_p, var->win_p);
	mlx_destroy_display(var->mlx_p);
	free(var->mlx_p);
	free(var);
	exit(0);
}

void	scaling_down(t_fdf *var)
{
	clear_image(var);
	var->map->radius -= RADIUS_SCALE;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_printf("Scaling down for %d coord Z\n", var->map->radius);
}

void	scaling_up(t_fdf *var)
{
	clear_image(var);
	var->map->radius += RADIUS_SCALE;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_printf("Scaling up for %d coord Z\n", var->map->radius);
}

void	reset(t_fdf *var)
{
	clear_image(var);
	var->map->radius = RADIUS_Z;
	var->img->distance = DISTANCE;
	var->map->p = 0;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_printf("Scaling up for %d coord Z\n", var->map->radius);
}

void	projection_change(t_fdf *var)
{
	var->map->p++;
	if (var->map->p > 2)
		var->map->p = 0;
	clear_image(var);
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_printf("Projection change\n");
}

int	key_hook(int keycode, t_fdf *var)
{
	if (keycode == XK_Escape)
		closer(var, keycode);
	if (keycode == XK_Up)
		going_up(var);
	if (keycode == XK_Down)
		going_down(var);
	if (keycode == XK_Left)
		going_left(var);
	if (keycode == XK_Right)
		going_right(var);
	if (keycode == XK_w)
		scaling_up(var);
	if (keycode == XK_s)
		scaling_down(var);
	if (keycode == XK_r)
		reset(var);
	if (keycode == XK_p)
		projection_change(var);
	var->i++;
	ft_printf("the %d key has been pressed\n", keycode);
	ft_printf("Key numbers pressed %d\n\n", var->i);
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

void	put_pixel(t_image *img, int x_d, int y_d, t_map *map, int x, int y)
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
	*(unsigned int *)(img->addr + index) = map->coord[y][x].color;
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

/* void	spherical_transform(float *x, float *y, float z)
{
	int	old_x;
	int	old_y;

	old_x = *x;
	old_y = *y;
	float r, theta, phi;
	r = sqrt(old_x * old_x + old_y * old_y + z * z);
	if (r == 0)
		return ;
	theta = atan2(old_y, old_x);
	phi = asin(z / r);
    *x = 300 * cos(phi) * sin(theta); // Scales to fit a circular area
    *y = 300 * sin(phi);
} */

void	draw_lineH(int dx, int dy, t_map *map, t_image *img, t_coord *tmp,
		int x, int y)
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
		put_pixel(img, tmp->x, tmp->y, map, x, y);
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

void	draw_lineV(int dx, int dy, t_map *map, t_image *img, t_coord *tmp,
		int x, int y)
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
		put_pixel(img, tmp->x, tmp->y, map, x, y);
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

void	draw_line(t_image *img, t_map *map, t_coord *next, int x, int y)
{
	int		dx;
	int		dy;
	t_coord	*tmp;

	tmp = point_init(map->x_d, map->y_d, map->z_d, COLOR);
	dx = (int)next->x - (int)map->x_d;
	dy = (int)next->y - (int)map->y_d;
	if (abs(dx) > abs(dy))
		draw_lineH(dx, dy, map, img, tmp, x, y);
	else
		draw_lineV(dx, dy, map, img, tmp, x, y);
	free(tmp);
}

void	chose_projection(t_fdf *var, float *x, float *y, float z)
{
	if (var->map->p == 0)
		isometric_transform(x, y, z);
	if (var->map->p == 1)
		dimetric_transform(x, y, z);
    //if (var->map->p == 2)
        //spherical_transform(x, y, z);
    //if (var->map->p == 4)
        
}

void	make_the_map(t_fdf *var, t_map *map, int x, int y)
{
	t_coord	*next;
	t_coord	*tmp;

	next = point_init(0, 0, 0, COLOR);
	tmp = point_init(map->x_d, map->y_d, map->z_d, COLOR);
	if (x == 0 && y == 0)
		map->coord[y][x].color = 0xFF0000;
	chose_projection(var, &map->x_d, &map->y_d, map->z_d);
	put_pixel(var->img, (int)map->x_d, (int)map->y_d, map, x, y);
	if (x < map->width - 1)
	{
		next->x = tmp->x + var->img->distance;
		next->y = tmp->y;
		next->z = map->coord[y][x + 1].z * (var->img->distance * map->radius);
		chose_projection(var, &next->x, &next->y, next->z);
		draw_line(var->img, map, next, x, y);
	}
	if (y < map->height - 1)
	{
		next->x = tmp->x;
		next->y = tmp->y + var->img->distance;
		next->z = map->coord[y + 1][x].z * (var->img->distance * map->radius);
		chose_projection(var, &next->x, &next->y, next->z);
		draw_line(var->img, map, next, x, y);
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
			make_the_map(var, map, x, y);
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
		// print_mapcoord(var->map);
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
