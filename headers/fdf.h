/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:15:34 by stdevis           #+#    #+#             */
/*   Updated: 2025/02/10 18:44:24 by stdevis          ###   ########.fr       */
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

# define HEIGHT 500
# define WIDTH 600

typedef struct s_map
{
	int		height;
	int		width;
	int		***array;
	int		z_max;
	int		z_min;
}			t_map;

typedef struct s_fdf
{
	int		i;
	void	*win;
	void	*mlx;
    t_map   *map;
}			t_fdf;


// initialization

void    initialization(t_fdf **var);

// free

void    free_fdf(t_fdf *var);
void    free_map(t_map *map);

// error

void ft_free_error(char *error, int check, t_fdf *var);
void ft_error(char *error);
void ft_perror(char *error);


#endif
