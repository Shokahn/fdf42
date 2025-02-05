/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:24:21 by stdevis           #+#    #+#             */
/*   Updated: 2025/01/21 13:39:13 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

void	ft_bzero(void *s, size_t n)
{
	int		i;
	char	*temp;

	i = 0;
	temp = (char *)s;
	while (n > 0)
	{
		temp[i] = 0;
		n--;
		i++;
	}
}

/*int	main(void)
{
	char str[] = "Hello everybody";
	char str1[] = "Hello everybody";
	bzero(str, 17);
	ft_bzero(str1, 17);
}*/