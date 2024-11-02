/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitris <dimitris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:34:37 by dchrysov          #+#    #+#             */
/*   Updated: 2024/11/01 21:15:11 by dimitris         ###   ########.fr       */
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
void			*ft_memcpy(void *dest, const void *src, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*get_next_line(int fd);
char			*ft_strndup(const char *s, unsigned long size);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
unsigned long	ft_strlen(const char str[]);


#endif