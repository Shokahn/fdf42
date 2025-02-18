/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:13:15 by stdevis           #+#    #+#             */
/*   Updated: 2025/02/18 15:15:36 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	initialization(t_fdf **var)
{
	*var = malloc(sizeof(t_fdf));
	if (!(*var))
		return ;
	(*var)->mlx = 0;
	(*var)->win = 0;
	(*var)->i = 0;
	(*var)->color = 0x00FF0000;
	(*var)->running = 1;
}

int	change_color(t_fdf *var)
{
	if (!var->running == 0)
		return (0);
	mlx_clear_window(var->mlx, var->win);
	mlx_string_put(var->mlx, var->win, 250, 250, var->color,
		"Color changing window!");
	if (var->color == 0x00FF0000)
		var->color = 0x0000FF00;
	else if (var->color == 0x0000FF00)
		var->color = 0x000000FF;
	else
		var->color = 0x00FF0000;
	usleep(200000);
	return (0);
}

int	closer(int keysyms, t_fdf *var)
{
	if (keysyms == XK_Escape)
	{
		ft_printf("the %d key (ESC) has been pressed\n\n", keysyms);
		ft_printf("end of the programme\n\n");
		mlx_destroy_window(var->mlx, var->win);
		mlx_destroy_display(var->mlx);
		free(var->mlx);
		free(var);
		exit(0);
	}
	if (keysyms == XK_space)
	{
		if (var->running == 1)
			var->running = 0;
		else
			var->running = 1;
		if (var->running == 1)
			ft_printf("color changing is off\n\n");
		else
			ft_printf("color changing is on\n\n");
	}
	var->i++;
	ft_printf("the %d key has been pressed\n\n", keysyms);
	ft_printf("Key numbers pressed %d\n\n", var->i);
	// change_color(var);
	return (0);
}

int	main(void)
{
	t_fdf	*var;

	initialization(&var);
	if (!var)
		return (1);
	var->mlx = mlx_init();
	if (!var->mlx)
	{
		free(var);
		return (1);
	}
	var->win = mlx_new_window(var->mlx, WIGHT, HEIGHT, "Void square");
	if (!var->win)
	{
		mlx_destroy_display(var->mlx);
		free(var->mlx);
		free(var);
		return (1);
	}
	mlx_loop_hook(var->mlx, change_color, var);
	mlx_key_hook(var->win, closer, var);
	mlx_loop(var->mlx);
	mlx_destroy_window(var->mlx, var->win);
	mlx_destroy_display(var->mlx);
	free(var->mlx);
	free(var);
	return (0);
}
