/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:13:15 by stdevis           #+#    #+#             */
/*   Updated: 2025/02/10 18:45:27 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

int	closer(int keysyms, t_fdf *var)
{
	if (keysyms == XK_Escape)
	{
		ft_printf("the %d key (ESC) has been pressed\n\n", keysyms);
		ft_printf("end of the programme\n\n");
		mlx_destroy_window(var->mlx, var->win);
		mlx_destroy_display(var->mlx);
		free(var->mlx);
		free(var);
		exit(0);
	}
	var->i++;
	ft_printf("the %d key has been pressed\n\n", keysyms);
	ft_printf("Key numbers pressed %d\n\n", var->i);
	return (0);
}

void	map_init(t_fdf *var, int fd)
{
	(void)fd;
	if (!var)
		exit(1);
	var->mlx = mlx_init();
	if (!var->mlx)
	{
		free(var);
		exit(1);
	}
	var->win = mlx_new_window(var->mlx, WIDTH, HEIGHT, "Void square");
	if (!var->win)
	{
		mlx_destroy_display(var->mlx);
		free(var->mlx);
		free(var);
		exit(1);
	}
	mlx_key_hook(var->win, closer, var);
	mlx_loop(var->mlx);
}

void	map_destruction(t_fdf *var)
{
	mlx_destroy_window(var->mlx, var->win);
	mlx_destroy_display(var->mlx);
	free(var->mlx);
	free(var);
}

int	map_read(t_fdf *var, char *map)
{
    int fd;
    int i;
    char *line;
    
    i = 0;
    fd = open(map, O_RDONLY);
    if (fd == -1)
        ft_free_error("open map failed", 1, var);
    line = get_next_line(fd);
    while(line)
    {
        parse_map(line, i, var->map);
        i++;
        
    
}

/// CONTINUE MAP READ TO PARSE MAP WITH ***ARRAY BUT WHY *** AND NOT ** ?

int	main(int ac, char **av)
{
	t_fdf	*var;
	int		fd;

	if (ac == 2)
	{
		initialization(&var);
		fd = map_read(var, av[1]);
		map_init(var, fd);
		map_destruction(var);
	}
	ft_putstr_fd(BOLD RED "Error : numbers of arguments\n" RESET, 2);
	ft_putstr_fd(ITALIC "Usage: ./fdf \"map.txt\"\n" RESET, 1);
	return (0);
}
