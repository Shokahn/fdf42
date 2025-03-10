/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:13:15 by stdevis           #+#    #+#             */
/*   Updated: 2025/03/10 14:28:24 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	chose_line_to_draw(t_fdf *var, t_map *map, t_coord *next, t_coord *tmp)
{
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
	chose_line_to_draw(var, map, next, tmp);
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
