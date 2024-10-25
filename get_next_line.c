/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:32:36 by dchrysov          #+#    #+#             */
/*   Updated: 2024/10/25 12:35:43 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	ssize_t			size;
	static char		*buffer;
	int				newlpos;
	char			*res;

	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return ("Error allocating memory");
	size = read(fd, buffer, BUFFER_SIZE);
	buffer[size] = '\0';
	newlpos = ft_strchr(buffer, '\n') - buffer;
	res = malloc(newlpos + 1);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, buffer, newlpos + 1);
	free(buffer);
	free(res);
	return (res);
}

// int	main(void)
// {
// 	char	*s;
//
// 	s = get_next_line(0);
// 	printf("%s", s);
// 	return (0);
// }