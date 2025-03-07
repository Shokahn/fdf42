/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling+zoom.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:15:33 by stdevis           #+#    #+#             */
/*   Updated: 2025/03/07 16:34:43 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	zoom_in(t_fdf *var)
{
	clear_image(var);
	var->img->distance += ZOOM;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}

void	zoom_out(t_fdf *var)
{
	if (var->img->distance - ZOOM <= 0)
		return ;
	clear_image(var);
	var->img->distance -= ZOOM;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}

void	scaling_down(t_fdf *var)
{
	clear_image(var);
	var->map->radius -= RADIUS_SCALE;
	if (var->map->max_z < var->map->min_z)
		ft_swap_float(&var->map->max_z, &var->map->min_z);
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}

void	scaling_up(t_fdf *var)
{
	clear_image(var);
	var->map->radius += RADIUS_SCALE;
	if (var->map->max_z < var->map->min_z)
		ft_swap_float(&var->map->max_z, &var->map->min_z);
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}
