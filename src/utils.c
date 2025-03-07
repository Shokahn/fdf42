/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:53:32 by stdevis           #+#    #+#             */
/*   Updated: 2025/03/07 19:25:58 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	clear_image(t_fdf *var)
{
	int	img_size;

	img_size = HEIGHT * WIGHT * 4;
	ft_memset(var->img->addr, 0, img_size);
}

void	ft_swap_float(float *x, float *y)
{
	float	*tmp;

	tmp = x;
	x = y;
	y = tmp;
}

void	ft_draw_instructions(t_fdf *var)
{
	mlx_string_put(var->mlx_p, var->win_p, 50, 50, 0xFFFFFF, "Molette : Zoom");
	mlx_string_put(var->mlx_p, var->win_p, 50, 80, 0xFFFFFF,
		"1 or 3  : ROTATE X");
	mlx_string_put(var->mlx_p, var->win_p, 50, 110, 0xFFFFFF,
		"4 or 6  : ROTATE Y");
	mlx_string_put(var->mlx_p, var->win_p, 50, 140, 0xFFFFFF,
		"7 or 9  : ROTATE Z");
	mlx_string_put(var->mlx_p, var->win_p, 50, 170, 0xFFFFFF,
		" Arrow  : Translate");
	mlx_string_put(var->mlx_p, var->win_p, 50, 200, 0xFFFFFF,
		"   R    : Reset");
	mlx_string_put(var->mlx_p, var->win_p, 50, 230, 0xFFFFFF,
		"   T    : Soft reset");
	mlx_string_put(var->mlx_p, var->win_p, 50, 260, 0xFFFFFF,
		"   P    : Change projection");
	mlx_string_put(var->mlx_p, var->win_p, 50, 290, 0xFFFFFF,
		"W or S  : Scaling");
}

int	mouse_hook(int keycode, int x, int y, t_fdf *var)
{
	(void)x;
	(void)y;
	if (keycode == 4)
		zoom_in(var);
	if (keycode == 5)
		zoom_out(var);
	return (0);
}

void	calculate_distance(t_fdf *var)
{
	int	distance_x;
	int	distance_y;

	distance_x = 0;
	distance_y = 0;
	if (var->map->width == 0 || var->map->height == 0)
		return ;
	while (var->map->width * distance_x < WIGHT - 1000)
		distance_x++;
	while (var->map->height * distance_y < HEIGHT - 1000)
		distance_y++;
	if (distance_x <= distance_y)
		var->img->distance = distance_x;
	else
		var->img->distance = distance_y;
}
