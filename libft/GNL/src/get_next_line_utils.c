/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:51:24 by stdevis           #+#    #+#             */
/*   Updated: 2025/01/23 14:49:51 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/get_next_line.h"

size_t	gnl_ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

ssize_t	gnl_ft_strchr(char *s, int c)
{
	ssize_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

char	*gnl_ft_strjoin(char *s1, char *s2)
{
	ssize_t	i;
	ssize_t	j;
	ssize_t	len1;
	ssize_t	len2;
	char	*str_join;

	if (!s1 || !s2)
		return (NULL);
	len1 = gnl_ft_strlen(s1);
	len2 = gnl_ft_strlen(s2);
	str_join = malloc(sizeof(char) * len1 + len2 + 1);
	if (!str_join)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		str_join[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str_join[i++] = s2[j++];
	str_join[i] = '\0';
	return (str_join);
}

char	*gnl_ft_substr(char *s, ssize_t start, size_t len)
{
	size_t	i;
	char	*substr;

	if (!s)
		return (NULL);
	i = 0;
	if (len > gnl_ft_strlen(s + start))
		len = gnl_ft_strlen(s + start);
	substr = malloc(sizeof(char) * len + 1);
	if (!substr)
		return (NULL);
	while (i < len)
	{
		substr[i] = s[i + start];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*gnl_ft_strdup(char *s1)
{
	char	*dup;
	size_t	i;
	size_t	len_s1;

	len_s1 = gnl_ft_strlen(s1);
	i = 0;
	dup = malloc(sizeof(char) * len_s1 + 1);
	if (!dup)
		return (NULL);
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
