/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:34:37 by dchrysov          #+#    #+#             */
/*   Updated: 2024/10/31 16:26:56 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 60
# endif

# include <stdlib.h>
# include <unistd.h>

void			*ft_memmove(void *dst, const void *src, size_t len);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*get_next_line(int fd);
char			*ft_strndup(const char *s, unsigned long size);
char			*ft_strjoin(char const *s1, char const *s2);
unsigned long	ft_strlen(const char str[]);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *s, int c);

#endif