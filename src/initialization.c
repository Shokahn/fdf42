/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:48:47 by stdevis           #+#    #+#             */
/*   Updated: 2025/02/10 18:34:20 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

t_map	*map_init(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->height = 0;
	map->width = 0;
	map->array = 0;
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
