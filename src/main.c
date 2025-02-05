/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:13:15 by stdevis           #+#    #+#             */
/*   Updated: 2025/02/04 19:03:59 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void initialization(t_mlx **var)
{
    *var = malloc(sizeof(t_mlx));
    if (!(*var))
        return;
    (*var)->mlx = 0;
    (*var)->win = 0;
    (*var)->i = 0;
}

int closer(int keycode, t_mlx *var)
{
    if (keycode == XK_Escape)
    {
        ft_printf("the %d key (ESC) has been pressed\n\n", keycode);
        mlx_destroy_window(var->mlx, var->win);
        mlx_destroy_display(var->mlx);
        free(var->mlx);
        free(var);
    }
    var->i++;
    ft_printf("the %d key has been pressed\n\n", keycode);
    ft_printf("Key numbers pressed %d\n\n", var->i);
    return (0);
}

int main()
{
    t_mlx *var;
    
    initialization(&var);
    if (!var)
        return (1);
    var->mlx = mlx_init();
    if  (!var->mlx)
    {
        free(var);
        return (1);
    }
    var->win = mlx_new_window(var->mlx, 1920, 1080, "Void square");
    if (!var->win)
    {
        mlx_destroy_display(var->mlx);
        free(var->mlx);
        free(var);
        return (1);
    }
    mlx_key_hook(var->win, closer, &var);
    mlx_loop(var->mlx);
    mlx_destroy_window(var->mlx, var->win);
    mlx_destroy_display(var->mlx);
    free(var->mlx);
    free(var);
    return (0);
}
