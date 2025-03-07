/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:08:34 by stdevis           #+#    #+#             */
/*   Updated: 2025/03/07 17:09:28 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

int	rgb_color(int color1, int color2, float ratio)
{
	int	r1;
	int	g1;
	int	b1;
	int	r;
	int	g;

	r1 = (color1 >> 16) & 0xFF;
	g1 = (color1 >> 8) & 0xFF;
	b1 = color1 & 0xFF;
	r = (int)(r1 + ((color2 >> 16) & (0xFF - r1)) * ratio);
	g = (int)(g1 + ((color2 >> 8) & (0xFF - g1)) * ratio);
	b1 = (color1 & 0xFF) + ((color2 & (0xFF - b1)) * ratio);
	return ((r << 16) | (g << 8) | b1);
}

void	get_color_start_end(t_map *map, int *color_start, int *color_end)
{
	if (map->color_check == 0)
	{
		*color_start = 0x373B44;
		*color_end = 0x4286f4;
	}
	if (map->color_check == 4)
	{
		*color_start = 0x159957;
		*color_end = 0x155799;
	}
	if (map->color_check == 2)
	{
		*color_start = 0x202020;
		*color_end = 0x0f9b0f;
	}
	if (map->color_check == 3)
	{
		*color_start = 0x616161;
		*color_end = 0x9bc5c3;
	}
	if (map->color_check == 1)
	{
		*color_start = 0x1D4350;
		*color_end = 0xA43931;
	}
}

int	get_color(t_map *map)
{
	int		color_start;
	int		color_end;
	float	true_z;
	float	percent;

	true_z = fabs(map->true_z);
	percent = (true_z - (map->min_z)) / ((map->max_z) - (map->min_z));
	if (percent < 0)
		percent = 0;
	if (percent > 1)
		percent = 1;
	get_color_start_end(map, &color_start, &color_end);
	return (rgb_color(color_start, color_end, percent));
}
