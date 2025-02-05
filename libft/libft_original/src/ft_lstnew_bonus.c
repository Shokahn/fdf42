/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:00:10 by stdevis           #+#    #+#             */
/*   Updated: 2025/01/21 13:47:41 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}

/*int main()
{
	char *content = "Yo la team";

	t_list	*new_elem = ft_lstnew(content);
	if (!new_elem)
		printf("Memory allocation failed\n");
	printf("%s\n", (char *)new_elem->content);
	if (new_elem->next == NULL)
		printf("Next pointer is NULL\n");
	free(new_elem);
}*/