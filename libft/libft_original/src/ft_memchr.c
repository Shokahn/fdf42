/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:52:51 by stdevis           #+#    #+#             */
/*   Updated: 2025/01/21 13:47:47 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_temp;
	size_t			i;

	s_temp = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (s_temp[i] == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}

/*int	main(void)
{
	char str1[] = "";
	char str2[] = "";

	printf("%s\n", ft_memchr(str1, '\0', 2));
	printf("%s\n", memchr(str2, '\0', 2));
}*/