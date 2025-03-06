/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shokahn <shokahn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:25:42 by shokahn           #+#    #+#             */
/*   Updated: 2025/03/06 15:19:32 by shokahn          ###   ########.fr       */
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

void	applicate_rotation(t_fdf *var, float *x, float*y, float *z)
{
	double angle;

	angle = 0.0872665;
	if (var->img->rotation_x != 0)
		rotate_x(y, z, (var->img->rotation_x * angle));
	if (var->img->rotation_y != 0)
		rotate_y(x, z, (var->img->rotation_y * angle));	
	if (var->img->rotation_z != 0)
		rotate_z(x, y, (var->img->rotation_z * angle));

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