/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:46:11 by stdevis           #+#    #+#             */
/*   Updated: 2025/02/11 18:00:37 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

void	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_array(int **array, int len)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (i < len)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_free_index(char **split, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(split[i]);
		i++;
	}
	free(split);
}
