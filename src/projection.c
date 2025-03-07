/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:58:32 by stdevis           #+#    #+#             */
/*   Updated: 2025/03/07 18:12:39 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	isometric_transform(float *x, float *y, float z)
{
	int	old_x;
	int	old_y;

	old_x = *x;
	old_y = *y;
	*x = (old_x - old_y) * cos(M_PI / 6);
	*y = (old_x + old_y) * sin(M_PI / 6) - z;
}

void	perspective_transform(float *x, float *y, float z, t_fdf *var)
{
	float	d;
	float	factor;

	d = (var->map->width * var->img->distance) * 5;
	if (z / d < -1)
		return ;
	factor = 1 / (1 + z / d);
	*x = *x * factor;
	*y = *y * factor;
}

void	chose_projection(t_fdf *var, float *x, float *y, float z)
{
	if (var->map->p == 0)
		isometric_transform(x, y, z);
	if (var->map->p == 1)
		perspective_transform(x, y, z, var);
	if (var->map->p == 2)
		*y = -z;
	if (var->map->p == 3)
	{
		*x = *y;
		*y = -z;
	}
}
