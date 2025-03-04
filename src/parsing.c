/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shokahn <shokahn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:35:55 by stdevis           #+#    #+#             */
/*   Updated: 2025/03/04 14:54:56 by shokahn          ###   ########.fr       */
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

void	fill_the_coord(char **split, t_map *map, int y)
{
	int	x;
	int nbr;
	
	x = 0;
	while (split[x] && x < map->width)
	{
		nbr = ft_atoi(split[x]);
		map->coord[y][x].z = nbr;
		if (map->max_z < nbr)
			map->max_z = nbr;
		if (map->min_z > nbr)
			map->min_z = nbr;
		x++;
	}
}

void	open_to_fill(int fd, t_fdf *var)
{
	int		y;
	char	*line;
	char	**split;

	y = 0;
	while (y < var->map->height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		split = ft_split(line, ' ');
		if (!split)
			ft_free_error("split for coord2 failed\n", 0, var);
		fill_the_coord(split, var->map, y);
		free(line);
		ft_free_tab(split);
		y++;
	}
	close(fd);
}

void	calculate_offset(t_fdf *var)
{
	int map_center_x; 
	int map_center_y; 
	int win_center_x; 
    int win_center_y;
		
	map_center_x = ((var->map->width - 1) / 2) * var->img->distance;
	map_center_y = (var->map->height / 2) * var->img->distance;

	win_center_x = WIGHT / 2;
	win_center_y = HEIGHT / 2;

    var->img->offset_x = win_center_x - map_center_x;
    var->img->offset_y = win_center_y - map_center_y;
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
	printf("height = %d, width = %d\n", var->map->height, var->map->width);
	open_to_fill(fd, var);
	calculate_offset(var);
	printf("max z = %f, min z = %f\n", var->map->max_z, var->map->min_z);
}
