/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:35:55 by stdevis           #+#    #+#             */
/*   Updated: 2025/02/22 16:52:51 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

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
	return (width - 1);
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
	line = get_next_line(fd); // pansement
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
		if (!line)
			break ;
		nbr = ft_split(line, ' ');
		if (!nbr)
			ft_free_error("split for coord2 failed\n", 0, var);
		fill_the_coord(nbr, var->map, y);
		free(line);
		ft_free_tab(nbr);
		y++;
	}
	close(fd);
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
	ft_printf("height = %d, width = %d\n", var->map->height, var->map->width);
	open_to_fill(fd, var);
}
