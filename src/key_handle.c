/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:51:12 by stdevis           #+#    #+#             */
/*   Updated: 2025/03/07 18:09:49 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	reset(t_fdf *var)
{
	clear_image(var);
	var->map->radius = RADIUS_Z;
	calculate_distance(var);
	var->map->p = 0;
	var->img->x = 0;
	var->img->y = 0;
	var->img->rotation_x = 0;
	var->img->rotation_y = 0;
	var->img->rotation_z = 0;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}

void	projection_change(t_fdf *var)
{
	var->map->p++;
	if (var->map->p > 4)
		var->map->p = 0;
	clear_image(var);
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}

void	reset_without_projection(t_fdf *var)
{
	clear_image(var);
	var->map->radius = RADIUS_Z;
	calculate_distance(var);
	var->img->x = 0;
	var->img->y = 0;
	var->img->rotation_x = 0;
	var->img->rotation_y = 0;
	var->img->rotation_z = 0;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}

void	change_color(t_fdf *var)
{
	clear_image(var);
	var->map->color_check++;
	if (var->map->color_check > 4)
		var->map->color_check = 0;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}

int	key_hook(int keycode, t_fdf *var)
{
	if (keycode == XK_Escape)
		closer(var);
	if (keycode == XK_Up || keycode == XK_Down || keycode == XK_Left
		|| keycode == XK_Right)
		translate(keycode, var);
	if (keycode == XK_w)
		scaling_up(var);
	if (keycode == XK_s)
		scaling_down(var);
	if (keycode == XK_r)
		reset(var);
	if (keycode == XK_p)
		projection_change(var);
	if (keycode == XK_t)
		reset_without_projection(var);
	if (keycode == XK_1 || keycode == XK_3 || keycode == XK_4 || keycode == XK_6
		|| keycode == XK_7 || keycode == XK_9)
		rotate(keycode, var);
	if (keycode == XK_space)
		change_color(var);
	return (0);
}
