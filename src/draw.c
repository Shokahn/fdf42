/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:57:01 by stdevis           #+#    #+#             */
/*   Updated: 2025/03/07 19:09:03 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	put_pixel(t_image *img, int x_d, int y_d, t_map *map)
{
	int	index;
	int	x_sized;
	int	y_sized;

	x_sized = x_d + WIGHT / 2;
	y_sized = y_d + HEIGHT / 4;
	if (img->x == 0 && img->y == 0)
	{
		if (x_sized <= 0 || x_sized >= WIGHT || y_sized <= 0
			|| y_sized >= HEIGHT)
			return ;
	}
	if (x_sized + img->x <= 0 || x_sized + img->x >= WIGHT || y_sized
		+ img->y <= 0 || y_sized + img->y >= HEIGHT)
		return ;
	index = (((y_sized + img->y) * img->line_lenght)) + (((x_sized + img->x)
				* (img->bpp / 8)));
	*(unsigned int *)(img->addr + index) = get_color(map);
}

void	draw_line_h(int dx, int dy, t_fdf *var, t_coord *tmp)
{
	int	p;
	int	i;
	int	step_x;
	int	step_y;

	step_x = 1;
	step_y = 1;
	if (dx < 0)
		step_x = -1;
	if (dy < 0)
		step_y = -1;
	p = 2 * abs(dy) - abs(dx);
	i = 0;
	while (i <= abs(dx))
	{
		put_pixel(var->img, tmp->x, tmp->y, var->map);
		tmp->x += step_x;
		if (p >= 0)
		{
			tmp->y += step_y;
			p -= 2 * abs(dx);
		}
		p += 2 * abs(dy);
		i++;
	}
}

void	draw_line_v(int dx, int dy, t_fdf *var, t_coord *tmp)
{
	int	p;
	int	i;
	int	step_x;
	int	step_y;

	step_x = 1;
	step_y = 1;
	if (dx < 0)
		step_x = -1;
	if (dy < 0)
		step_y = -1;
	p = 2 * abs(dx) - abs(dy);
	i = 0;
	while (i <= abs(dy))
	{
		put_pixel(var->img, tmp->x, tmp->y, var->map);
		tmp->y += step_y;
		if (p >= 0)
		{
			tmp->x += step_x;
			p -= 2 * abs(dy);
		}
		p += 2 * abs(dx);
		i++;
	}
}

void	draw_line(t_fdf *var, t_coord *next)
{
	int		dx;
	int		dy;
	t_coord	*tmp;

	tmp = point_init(var->map->x_d, var->map->y_d, var->map->z_d, 0);
	dx = (int)next->x - (int)var->map->x_d;
	dy = (int)next->y - (int)var->map->y_d;
	if (abs(dx) > abs(dy))
		draw_line_h(dx, dy, var, tmp);
	else
		draw_line_v(dx, dy, var, tmp);
	free(tmp);
}
