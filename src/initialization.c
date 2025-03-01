/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:48:47 by stdevis           #+#    #+#             */
/*   Updated: 2025/03/01 16:04:36 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

t_coord	**coord_init(int height, int width, t_fdf *var)
{
	int		y;
	int		x;
	t_coord	**coord;

	y = 0;
	coord = malloc(sizeof(t_coord *) * height);
	if (!coord)
		ft_free_error("malloc coord failed\n", 0, var);
	while (y < height)
	{
		coord[y] = malloc(sizeof(t_coord) * width);
		if (!coord[y])
		{
			free_coord_index(coord, y);
			ft_free_error("malloc coord[i] failed\n", 0, var);
		}
		x = 0;
		while (x < width)
		{
			coord[y][x].x = x;
			coord[y][x].y = y;
			coord[y][x].z = 0;
			coord[y][x].color = COLOR;
			coord[y][x].true_zero = 0;
			x++;
		}
		y++;
	}
	return (coord);
}

t_map	*map_init(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->height = 0;
	map->width = 0;
	map->max_z = 0;
	map->min_z = 0;
	map->coord = NULL;
	map->x_d = 0;
	map->y_d = 0;
	map->z_d = 0;
    map->x_index = 0;
    map->y_index = 0;
    map->p = 0;
    map->radius = RADIUS_Z;
	return (map);
}

t_image	*img_init(void)
{
	t_image	*img;

	img = malloc(sizeof(t_image));
	if (!img)
		return (NULL);
	img->addr = NULL;
	img->bpp = 0;
	img->endian = 0;
	img->img_p = NULL;
	img->line_lenght = 0;
	img->distance = DISTANCE;
	img->x = 0;
	img->y = 0;
	return (img);
}

void	initialization(t_fdf **var)
{
	*var = malloc(sizeof(t_fdf));
	if (!(*var))
		return ;
	(*var)->mlx_p = 0;
	(*var)->win_p = 0;
	(*var)->map = map_init();
	(*var)->img = img_init();
	if (!(*var)->map)
		ft_free_error("initialization of the map failed\n", 0, *var);
	if (!(*var)->img)
		ft_free_error("initialization of the img failed\n", 0, *var);
}

t_coord	*point_init(int x, int y, int z, int color)
{
	t_coord *point;

	point = malloc(sizeof(t_coord));
	if (!point)
		return (NULL);
	point->x = x;
	point->y = y;
	point->z = z;
	point->color = color;
	return (point);
}