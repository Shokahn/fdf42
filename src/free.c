/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:28:47 by stdevis           #+#    #+#             */
/*   Updated: 2025/02/17 14:03:21 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void    free_coord(t_coord **coord)
{
    int i;
    
    if (!coord)
        return ;
    i = 0;
    while(coord[i])
    {
        free(coord[i]);
        i++;
    }
    free(coord);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	free_coord(map->coord);
	free(map);
}

void	free_fdf(t_fdf *var)
{
	if (!var)
		return ;
	free_map(var->map);
    free(var->img);
	free(var);
}

void	free_coord_index(t_coord **coord, int j)
{
	int i;

	i = 0;
	while (i < j)
	{
		free(coord[i]);
		i++;
	}
	free(coord);
}
