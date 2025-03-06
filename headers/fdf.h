/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shokahn <shokahn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:15:34 by stdevis           #+#    #+#             */
/*   Updated: 2025/03/06 14:07:55 by shokahn          ###   ########.fr       */
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
# include <float.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define HEIGHT 800
# define WIGHT 800
# define RADIUS_Z 0.8
# define RADIUS_SCALE 0.02
# define SCALING 0.5
# define DEPLACEMENT 20
# define ZOOM 2
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
	int		color;
}			t_coord;

typedef struct s_color
{
	int start;
	int end;
}			t_color;

typedef struct s_map
{
	int		height;
	int		width;
	int		p;
	float	max_z;
	float	min_z;
	t_coord	**coord;
	int		color_check;
	t_color	*color;
	float	x_d;
	float	y_d;
	float	z_d;
	float	radius;
	int		x_index;
	int		y_index;
	float	true_z;
}			t_map;

typedef struct s_image
{
	float	distance;
	float	offset_x;
	float	offset_y;
	float	rotation_x;
	float	rotation_y;
	float	rotation_z;
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
void	calculate_distance(t_fdf *var);

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

void		translate(int keycode, t_fdf *var);

// rotate

void	rotate(int keycode, t_fdf *var);
void	applicate_rotation(t_fdf *var, float *x, float*y, float *z);

void	ft_draw_instructions(t_fdf *var);

#endif