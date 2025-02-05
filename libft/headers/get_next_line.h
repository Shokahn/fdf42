/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:12:47 by stdevis           #+#    #+#             */
/*   Updated: 2025/01/23 14:42:50 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# ifndef MAX_BUFFER_SIZE
#  define MAX_BUFFER_SIZE 8383576
# endif

# ifndef MAX_FD
#  define MAX_FD 10239
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

ssize_t	gnl_ft_strchr(char *s, int c);
size_t	gnl_ft_strlen(char *s);
char	*gnl_ft_strjoin(char *s1, char *s2);
char	*gnl_ft_substr(char *s, ssize_t start, size_t len);
char	*gnl_ft_strdup(char *s1);
char	*create_rest(char *line);
char	*read_the_line(int fd, char *rest);
char	*get_next_line(int fd);
void	gnl_ft_free(char **str);
char	*get_the_line(char *rest, char *buff);

#endif