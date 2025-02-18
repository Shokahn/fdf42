/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:15:34 by stdevis           #+#    #+#             */
/*   Updated: 2025/02/18 15:59:06 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/headers/ft_printf.h"
# include "../libft/headers/get_next_line.h"
# include "../libft/headers/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define HEIGHT 1500
# define WIGHT 1800
# define DISTANCE 5
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define TEST ft_printf(BOLD GREEN "TEST\n" RESET)
# define TEST2 ft_printf(BOLD RED "TEST\n" RESET)

typedef struct s_coord
{
	int		x;
	int		y;
	int		z;
}			t_coord;

typedef struct s_map
{
	int		height;
	int		width;
	t_coord	**coord;
	int		z_max;
	int		z_min;
}			t_map;

typedef struct s_image
{
	void	*img_p;
	char	*addr;
	int		bpp;
	int		line_lenght;
	int		endian;
}			t_image;

typedef struct s_fdf
{
	int		i;
	void	*win_p;
	void	*mlx_p;
	int		running;
	int		color;
	t_map	*map;
	t_image	*img;
}			t_fdf;

// initialization

void		initialization(t_fdf **var);
t_coord		**coord_init(int height, int width, t_fdf *var);
t_map		*map_init(void);

// parsing

void		map_read(t_fdf *var, char *map_name);
// free

void		free_fdf(t_fdf *var);
void		free_map(t_map *map);
void		free_coord_index(t_coord **coord, int j);
void		free_coord(t_coord **coord);

// error

void		ft_error(char *error);
void		ft_perror(char *error);
void		ft_free_error(char *error, int check, t_fdf *var);

// print

void		print_mapcoord(t_map *map);
void		print_tab(char **nbr);

#endif