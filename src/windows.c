/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:16:41 by stdevis           #+#    #+#             */
/*   Updated: 2025/03/07 17:46:04 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	wind_init(t_fdf *var)
{
	if (!var)
		exit(1);
	var->mlx_p = mlx_init();
	if (!var->mlx_p)
	{
		free_fdf(var);
		exit(1);
	}
	var->win_p = mlx_new_window(var->mlx_p, WIGHT, HEIGHT, "fdf");
	if (!var->win_p)
	{
		mlx_destroy_display(var->mlx_p);
		ft_free_error("destroy wind failed\n", 0, var);
	}
	var->img->img_p = mlx_new_image(var->mlx_p, WIGHT, HEIGHT);
}

void	wind_destruction(t_fdf *var)
{
	mlx_destroy_image(var->mlx_p, var->img->img_p);
	mlx_destroy_window(var->mlx_p, var->win_p);
	mlx_destroy_display(var->mlx_p);
	free(var->mlx_p);
	free_fdf(var);
}

int	closer(t_fdf *var)
{
	ft_printf("the ESC key or red cross has been pressed\n");
	mlx_destroy_image(var->mlx_p, var->img->img_p);
	mlx_destroy_window(var->mlx_p, var->win_p);
	mlx_destroy_display(var->mlx_p);
	ft_free_error("end of the programme\n", 0, var);
	exit(0);
}
