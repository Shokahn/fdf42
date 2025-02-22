/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:24:48 by stdevis           #+#    #+#             */
/*   Updated: 2025/02/21 19:49:37 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	going_up(t_fdf *var)
{
	clear_image(var);
	var->img->y += DEPLACEMENT;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_printf("going up !\n");
}

void	going_down(t_fdf *var)
{
	clear_image(var);
	var->img->y -= DEPLACEMENT;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_printf("going down !\n");
}

void	going_left(t_fdf *var)
{
	clear_image(var);
	var->img->x += DEPLACEMENT;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_printf("going left !\n");
}

void	going_right(t_fdf *var)
{
	clear_image(var);
	var->img->x -= DEPLACEMENT;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_printf("going right !\n");
}
