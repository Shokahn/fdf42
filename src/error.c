/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:21:53 by stdevis           #+#    #+#             */
/*   Updated: 2025/02/10 18:32:49 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void ft_perror(char *error)
{
    perror(error);
    exit(1);
}

void ft_error(char *error)
{
    ft_putstr_fd(error, 2);
    exit(1);
}

void ft_free_error(char *error, int check, t_fdf *var)
{
    free_fdf(var);
    if (check == 1)
        ft_perror(error);
    else if (check == 0)
        ft_error(error);
}
