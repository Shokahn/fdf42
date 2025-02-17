/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:13:15 by stdevis           #+#    #+#             */
/*   Updated: 2025/02/17 15:15:11 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

int	closer(int keysyms, t_fdf *var)
{
	if (keysyms == XK_Escape)
	{
		ft_printf("the %d key (ESC) has been pressed\n\n", keysyms);
		ft_printf("end of the programme\n\n");
		mlx_destroy_window(var->mlx_p, var->win_p);
		mlx_destroy_display(var->mlx_p);
		free(var->mlx_p);
		free(var);
		exit(0);
	}
	var->i++;
	ft_printf("the %d key has been pressed\n\n", keysyms);
	ft_printf("Key numbers pressed %d\n\n", var->i);
	return (0);
}

void	wind_init(t_fdf *var, int height, int width)
{
	if (!var)
		exit(1);
	var->mlx_p = mlx_init();
	if (!var->mlx_p)
	{
		free(var);
		exit(1);
	}
	var->win_p = mlx_new_window(var->mlx_p, width * 15, height * 15, "fdf");
	if (!var->win_p)
	{
		mlx_destroy_display(var->mlx_p);
		free(var->mlx_p);
		free(var);
		exit(1);
	}
	var->img->img_p = mlx_new_image(var->mlx_p, width * 10, height * 10);
}

void	wind_destruction(t_fdf *var)
{
    mlx_destroy_image(var->mlx_p, var->img->img_p);
	mlx_destroy_window(var->mlx_p, var->win_p);
	mlx_destroy_display(var->mlx_p);
	free(var->mlx_p);
	free(var);
}

void	put_pixel(t_fdf *var, int x, int y, int color)
{
	int	index;
    int i;
    
    i = 0;
    while(i < 5000)
    {
        if (x + i < 0 || x + i >= var->map->width * 100 || y < 0)
            return ;
        index = (y * var->img->line_lenght) + ((x + i) * (var->img->bpp / 8));
	    *(unsigned int *)(var->img->addr + index) = color;
        i++;
    }
}
void	resolve_image(t_fdf *var)
{
	var->img->addr = mlx_get_data_addr(var->img->img_p, &var->img->bpp,
			&var->img->line_lenght, &var->img->endian);
	put_pixel(var, 1, 1, 0xFFFFFF);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p,
		var->map->width * 10, var->map->height * 10);
	mlx_key_hook(var->win_p, closer, var);
	mlx_loop(var->mlx_p);
}

int	main(int ac, char **av)
{
	t_fdf	*var;

	if (ac == 2)
	{
		initialization(&var);
		map_read(var, av[1]);
		print_mapcoord(var->map);
		wind_init(var, (var->map->height * 10), (var->map->width * 10));
		resolve_image(var);
		wind_destruction(var);
	}
	else
	{
		ft_putstr_fd(BOLD RED "Error : numbers of arguments\n" RESET, 2);
		ft_putstr_fd(ITALIC "Usage: ./fdf \"map.fdf\"\n" RESET, 1);
		return (1);
	}
	return (0);
}
