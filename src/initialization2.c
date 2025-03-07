/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intialization2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:30:15 by stdevis           #+#    #+#             */
/*   Updated: 2025/03/07 19:35:36 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	init_the_coord(t_coord **coord, int x, int y)
{
	coord[y][x].x = x;
	coord[y][x].y = y;
	coord[y][x].z = 0;
	coord[y][x].color = 0;
}

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
			init_the_coord(coord, x, y);
			x++;
		}
		y++;
	}
	return (coord);
}
