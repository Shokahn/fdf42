/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:08:05 by stdevis           #+#    #+#             */
/*   Updated: 2025/03/07 16:29:15 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	print_mapcoord(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			ft_printf("for coord[y %d][x %d] z = %d\n", map->coord[y][x].y,
				map->coord[y][x].x, map->coord[y][x].z);
			x++;
		}
		y++;
	}
}

void	print_tab(char **nbr)
{
	int	i;

	i = 0;
	while (nbr[i])
	{
		ft_printf("%s\n", nbr[i]);
		i++;
	}
}
