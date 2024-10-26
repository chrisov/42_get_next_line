/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:34:37 by dchrysov          #+#    #+#             */
/*   Updated: 2024/10/26 16:13:28 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 60
# endif

# include <stdlib.h>
# include <unistd.h>

unsigned long	ft_strlen(const char str[]);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*get_next_line(int fd);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);

#endif