/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:48:47 by stdevis           #+#    #+#             */
/*   Updated: 2025/02/11 19:15:18 by stdevis          ###   ########.fr       */
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
			free_struct_index(coord, y);
			ft_free_error("malloc coord[i] failed\n", 0, var);
		}
        x = 0;
		while(x < width)
        {
            coord[y][x].x = x;
            coord[y][x].y = y;
            coord[y][x].z = 0;
        }
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
	map->coord = NULL;
	map->z_max = 0;
	map->z_min = 0;
	return (map);
}

void	initialization(t_fdf **var)
{
	*var = malloc(sizeof(t_fdf));
	if (!(*var))
		return ;
	(*var)->mlx = 0;
	(*var)->win = 0;
	(*var)->i = 0;
	(*var)->map = map_init();
	if (!(*var)->map)
		ft_free_error("initialization of the map failed\n", 0, *var);
}
