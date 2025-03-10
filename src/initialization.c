/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:48:47 by stdevis           #+#    #+#             */
/*   Updated: 2025/03/10 14:19:23 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

t_color	*color_init(void)
{
	t_color	*color;

	color = malloc(sizeof(t_color));
	if (!color)
		return (NULL);
	color->start = 0;
	color->end = 0;
	return (color);
}

t_map	*map_init(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->height = 0;
	map->width = 0;
	map->max_z = FLT_MIN;
	map->min_z = FLT_MAX;
	map->coord = NULL;
	map->x_d = 0;
	map->y_d = 0;
	map->z_d = 0;
	map->x_index = 0;
	map->y_index = 0;
	map->p = 0;
	map->radius = RADIUS_Z;
	map->true_z = 0;
	map->color = color_init();
	map->color_check = 0;
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
	img->distance = 0;
	img->offset_x = 0;
	img->offset_y = 0;
	img->rotation_x = 0;
	img->rotation_y = 0;
	img->rotation_z = 0;
	img->x = 0;
	img->y = 0;
	img->height_menu = 0;
	img->width_menu = 0;
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
	t_coord	*point;

	point = malloc(sizeof(t_coord));
	if (!point)
		return (NULL);
	point->x = x;
	point->y = y;
	point->z = z;
	point->color = color;
	return (point);
}
