/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:13:15 by stdevis           #+#    #+#             */
/*   Updated: 2025/02/18 16:15:57 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

int	closer(int keysyms, t_fdf *var)
{
	if (keysyms == XK_Escape)
	{
		ft_printf("the %d key (ESC) has been pressed\n\n", keysyms);
		ft_printf("end of the programme\n\n");
		mlx_destroy_image(var->mlx_p, var->img->img_p);
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

void	put_pixel(t_fdf *var, int x, int y, int color)
{
	int	index;

	if (x < 0 || x > WIGHT || y < 0 || y > HEIGHT)
	{
		return ;
	}
	index = (y * var->img->line_lenght) + (x * (var->img->bpp / 8));
	*(unsigned int *)(var->img->addr + index) = color;
}

void	isometric_transform(int *x, int *y, int z)
{
	int	old_x;
	int	old_y;

	old_x = *x;
	old_y = *y;
	*x = (old_x - old_y) * cos(M_PI / 6);     // cos(30°)
	*y = (old_x + old_y) * sin(M_PI / 6) - z; // sin(30°) - z
}

void	put_the_grid(t_fdf *var, t_map *map)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	z;

	j = 0;
	while (j < map->height)
	{
		i = 0;
		while (i < map->width)
		{
			x = i * DISTANCE;
			y = j * DISTANCE;
			z = map->coord[j][i].z * DISTANCE;
			isometric_transform(&x, &y, z);
			put_pixel(var, x + (WIGHT / 2), y + (HEIGHT / 4), 0xFF00FF);
			i++;
		}
		j++;
	}
}

void	resolve_image(t_fdf *var)
{
	var->img->addr = mlx_get_data_addr(var->img->img_p, &var->img->bpp,
			&var->img->line_lenght, &var->img->endian);
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
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
		wind_init(var);
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
