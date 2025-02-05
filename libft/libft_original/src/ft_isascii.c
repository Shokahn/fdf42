/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:40:27 by stdevis           #+#    #+#             */
/*   Updated: 2025/01/21 13:47:17 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

/*int	main(void)
{
	printf("%d\n%d\n%d\n%d\n\n\n", ft_isascii(-15), ft_isascii(135),
	ft_isascii('\0'), ft_isascii('a'));
	printf("%d\n%d\n%d\n%d\n", isascii(-15), isascii(135),
	isascii('\0'), isascii('a'));
}*/