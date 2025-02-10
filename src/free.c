/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:28:47 by stdevis           #+#    #+#             */
/*   Updated: 2025/02/10 18:31:09 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void    free_map(t_map *map)
{
    if (!map)
        return ;
    free(map->array);
    free(map);   
}

void    free_fdf(t_fdf *var)
{
    if (!var)
        return ;
    free_map(var->map);
    free(var);
}
