/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:13:15 by stdevis           #+#    #+#             */
/*   Updated: 2025/02/11 19:31:42 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

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
	var->i++;
	ft_printf("the %d key has been pressed\n\n", keysyms);
	ft_printf("Key numbers pressed %d\n\n", var->i);
	return (0);
}

void	wind_init(t_fdf *var)
{
	if (!var)
		exit(1);
	var->mlx = mlx_init();
	if (!var->mlx)
	{
		free(var);
		exit(1);
	}
	var->win = mlx_new_window(var->mlx, WIDTH, HEIGHT, "Void square");
	if (!var->win)
	{
		mlx_destroy_display(var->mlx);
		free(var->mlx);
		free(var);
		exit(1);
	}
	mlx_key_hook(var->win, closer, var);
	mlx_loop(var->mlx);
}

void	wind_destruction(t_fdf *var)
{
	mlx_destroy_window(var->mlx, var->win);
	mlx_destroy_display(var->mlx);
	free(var->mlx);
	free(var);
}

int	calculate_width(char *line)
{
	char	**nbr;
	int		width;

	width = 0;
	nbr = ft_split(line, ' ');
	if (!nbr)
		return (0);
	while (nbr[width])
		width++;
	ft_free_tab(nbr);
	return (width);
}

void	find_height_width(t_fdf *var, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (var->map->height == 0)
			var->map->width = calculate_width(line);
		if (var->map->width == 0)
			ft_free_error("split for width failed\n", 0, var);
		var->map->height++;
		free(line);
	}
	close(fd);
}

void	fill_the_coord(char **nbr, t_map *map, int y)
{
	int	x;

	x = 0;
	while (nbr[x] && x < map->width)
	{
		map->coord[y][x].z = ft_atoi(nbr[x]);
		x++;
	}
}

void	open_to_fill(int fd, t_fdf *var)
{
	int		y;
	char	*line;
	char	**nbr;

	y = 0;
	while (y < var->map->height)
	{
		line = get_next_line(fd);
		nbr = ft_split(line, ' ');
		if (!nbr)
			ft_free_error("split for coord failed\n", 0, var);
		fill_the_coord(nbr, var->map, y);
		ft_free_tab(nbr);
        y++;
	}
}

void	map_read(t_fdf *var, char *map_name)
{
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		ft_free_error("map open failed\n", 1, var);
	find_height_width(var, fd);
   	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		ft_free_error("map open failed\n", 1, var);
	var->map->coord = coord_init(var->map->height, var->map->width, var);
	open_to_fill(fd, var);
    close(fd);
}

int	main(int ac, char **av)
{
	t_fdf	*var;

	if (ac == 2)
	{
		initialization(&var);
		map_read(var, av[1]);
		// wind_init(var);
		// wind_destruction(var);
	}
	ft_putstr_fd(BOLD RED "Error : numbers of arguments\n" RESET, 2);
	ft_putstr_fd(ITALIC "Usage: ./fdf \"map.fdf\"\n" RESET, 1);
	return (0);
}
