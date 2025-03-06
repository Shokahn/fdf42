/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shokahn <shokahn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:24:48 by stdevis           #+#    #+#             */
/*   Updated: 2025/03/05 17:17:20 by shokahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	going_up(t_fdf *var)
{
	clear_image(var);
	var->img->y += DEPLACEMENT;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}

void	going_down(t_fdf *var)
{
	clear_image(var);
	var->img->y -= DEPLACEMENT;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}

void	going_left(t_fdf *var)
{
	clear_image(var);
	var->img->x += DEPLACEMENT;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}

void	going_right(t_fdf *var)
{
	clear_image(var);
	var->img->x -= DEPLACEMENT;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}

void	translate(int keycode, t_fdf *var)
{
	if (keycode == XK_Up)
		going_up(var);
	if (keycode == XK_Down)
		going_down(var);
	if (keycode == XK_Left)
		going_left(var);
	if (keycode == XK_Right)
		going_right(var);
}
