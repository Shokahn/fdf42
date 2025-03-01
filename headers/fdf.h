/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:15:34 by stdevis           #+#    #+#             */
/*   Updated: 2025/03/01 16:03:42 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/headers/ft_printf.h"
# include "../libft/headers/get_next_line.h"
# include "../libft/headers/libft.h"
# include "../minilibx_macos/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>


# define HEIGHT 1800
# define WIGHT 1500
# define RADIUS_Z 0.8
# define SCALING 0.5
# define DISTANCE 20
# define DEPLACEMENT 20
# define ZOOM 2
# define COLOR 0x33ff99
# define K 2
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define TEST ft_printf(BOLD GREEN "TEST\n\n" RESET)
# define TEST2 ft_printf(BOLD RED "TEST\n\n" RESET)

typedef struct s_coord
{
	float	x;
	float	y;
	float	z;
	int		true_zero;
	int		color;
}			t_coord;

typedef struct s_map
{
	int		height;
	int		width;
	int		p;
	float	max_z;
	float	min_z;
	t_coord	**coord;
	float	x_d;
	float	y_d;
	float	z_d;
	float	radius;
	int		x_index;
	int		y_index;
}			t_map;

typedef struct s_image
{
	float	distance;
	float	start_x;
	float	star_y;
	void	*img_p;
	char	*addr;
	int		bpp;
	int		line_lenght;
	int		endian;
	int x; // deplacement
	int		y;
}			t_image;

typedef struct s_fdf
{
	void	*win_p;
	void	*mlx_p;
	t_map	*map;
	t_image	*img;
}			t_fdf;

// initialization

void		initialization(t_fdf **var);
t_coord		**coord_init(int height, int width, t_fdf *var);
t_map		*map_init(void);
t_coord		*point_init(int x, int y, int z, int color);

// parsing

void		map_read(t_fdf *var, char *map_name);

//  put_the_image

void		put_the_grid(t_fdf *var, t_map *map);
void		clear_image(t_fdf *var);

// free

void		free_fdf(t_fdf *var);
void		free_map(t_map *map);
void		free_coord_index(t_coord **coord, int j);
void		free_coord(t_coord **coord, int width);

// error

void		ft_error(char *error);
void		ft_perror(char *error);
void		ft_free_error(char *error, int check, t_fdf *var);

// print

void		print_mapcoord(t_map *map);
void		print_tab(char **nbr);

// translation

void		going_up(t_fdf *var);
void		going_down(t_fdf *var);
void		going_left(t_fdf *var);
void		going_right(t_fdf *var);

#endif