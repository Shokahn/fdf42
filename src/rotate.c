/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:25:42 by shokahn           #+#    #+#             */
/*   Updated: 2025/03/07 19:06:18 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

static void	rotate_x(float *y, float *z, double x_angle)
{
	int	prev_y;

	prev_y = *y;
	*y = prev_y * cos(x_angle) + *z * sin(x_angle);
	*z = prev_y * -sin(x_angle) + *z * cos(x_angle);
}

static void	rotate_y(float *x, float *z, double y_angle)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(y_angle) + *z * sin(y_angle);
	*z = prev_x * -sin(y_angle) + *z * cos(y_angle);
}

static void	rotate_z(float *x, float *y, double z_angle)
{
	t_coord	prev;

	prev.x = *x;
	prev.y = *y;
	*x = prev.x * cos(z_angle) - prev.y * sin(z_angle);
	*y = prev.x * sin(z_angle) + prev.y * cos(z_angle);
}

void	applicate_rotation(t_fdf *var, float *x, float *y, float *z)
{
	double	angle;
	float	center_x;
	float	center_y;
	float	center_z;
	t_coord	original;

	angle = 0.0872665;
	center_x = (var->map->width - 1) * (var->img->distance / 2);
	center_y = (var->map->height - 1) * (var->img->distance / 2);
	center_z = (var->map->max_z + var->map->min_z) / 2;
	original.x = *x - center_x;
	original.y = *y - center_y;
	original.z = *z - center_z;
	if (var->img->rotation_x != 0)
		rotate_x(&original.y, &original.z, (var->img->rotation_x * angle));
	if (var->img->rotation_y != 0)
		rotate_y(&original.x, &original.z, (var->img->rotation_y * angle));
	if (var->img->rotation_z != 0)
		rotate_z(&original.x, &original.y, (var->img->rotation_z * angle));
	*x = original.x + center_x;
	*y = original.y + center_y;
	*z = original.z + center_z;
}

void	rotate(int keycode, t_fdf *var)
{
	clear_image(var);
	if (keycode == XK_1)
		var->img->rotation_x += 1;
	if (keycode == XK_3)
		var->img->rotation_x -= 1;
	if (keycode == XK_4)
		var->img->rotation_y += 1;
	if (keycode == XK_6)
		var->img->rotation_y -= 1;
	if (keycode == XK_7)
		var->img->rotation_z += 1;
	if (keycode == XK_9)
		var->img->rotation_z -= 1;
	put_the_grid(var, var->map);
	mlx_put_image_to_window(var->mlx_p, var->win_p, var->img->img_p, 0, 0);
	ft_draw_instructions(var);
}
