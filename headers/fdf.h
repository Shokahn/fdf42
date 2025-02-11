/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:15:34 by stdevis           #+#    #+#             */
/*   Updated: 2025/02/11 19:17:58 by stdevis          ###   ########.fr       */
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

# define HEIGHT 800
# define WIDTH 1000

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

typedef struct s_fdf
{
	int		i;
	void	*win;
	void	*mlx;
	t_map	*map;
}			t_fdf;

// initialization

void		initialization(t_fdf **var);
t_coord		**coord_init(int height, int width, t_fdf *var);
t_map		*map_init(void);

// free

void		free_fdf(t_fdf *var);
void		free_map(t_map *map);
void		free_struct_index(t_coord **coord, int j);

// error

void		ft_error(char *error);
void		ft_perror(char *error);
void		ft_free_error(char *error, int check, t_fdf *var);

#endif