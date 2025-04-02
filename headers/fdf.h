/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:15:34 by stdevis           #+#    #+#             */
/*   Updated: 2025/04/02 15:10:09 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/headers/ft_printf.h"
# include "../libft/headers/get_next_line.h"
# include "../libft/headers/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define HEIGHT 1800
# define WIGHT 1800
# define RADIUS_Z 0.8
# define RADIUS_SCALE 0.02
# define SCALING 0.5
# define DEPLACEMENT 20
# define ZOOM 2
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define FLT_MAX 3.402823466e+38F
# define FLT_MIN 1.175494351e-38F

typedef struct s_coord
{
	float	x;
	float	y;
	float	z;
	int		color;
}			t_coord;

typedef struct s_color
{
	int		start;
	int		end;
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
	int		width_menu;
	int		height_menu;
	void	*img_p;
	char	*addr;
	int		bpp;
	int		line_lenght;
	int		endian;
	int		x;
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
void		calculate_distance(t_fdf *var);

//  put_the_image

void		put_the_grid(t_fdf *var, t_map *map);
void		clear_image(t_fdf *var);

// draw

void		put_pixel(t_image *img, int x_d, int y_d, t_map *map);
void		draw_line_h(int dx, int dy, t_fdf *var, t_coord *tmp);
void		draw_line_v(int dx, int dy, t_fdf *var, t_coord *tmp);
void		draw_line(t_fdf *var, t_coord *next);

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

void		rotate(int keycode, t_fdf *var);
void		applicate_rotation(t_fdf *var, float *x, float *y, float *z);

// scaling+zoom

void		zoom_in(t_fdf *var);
void		zoom_out(t_fdf *var);
void		scaling_down(t_fdf *var);
void		scaling_up(t_fdf *var);

// color

int			rgb_color(int color1, int color2, float ratio);
void		get_color_start_end(t_map *map, int *color_start, int *color_end);
int			get_color(t_map *map);

// win

void		wind_init(t_fdf *var);
int			closer(t_fdf *var);
void		wind_destruction(t_fdf *var);

// key

int			key_hook(int keycode, t_fdf *var);
void		change_color(t_fdf *var);
void		reset_without_projection(t_fdf *var);
void		projection_change(t_fdf *var);
void		reset(t_fdf *var);

// utils

void		clear_image(t_fdf *var);
void		ft_swap_float(float *x, float *y);
void		ft_draw_instructions(t_fdf *var);
void		calculate_distance(t_fdf *var);
int			mouse_hook(int keycode, int x, int y, t_fdf *var);

// projection

void		chose_projection(t_fdf *var, float *x, float *y, float z);
void		perspective_transform(float *x, float *y, float z, t_fdf *var);
void		isometric_transform(float *x, float *y, float z);

#endif