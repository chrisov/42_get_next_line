/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitris <dimitris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:32:36 by dchrysov          #+#    #+#             */
/*   Updated: 2024/10/25 21:43:26 by dimitris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	ssize_t			size;
	static char		*buffer;
	int				delpos;
	char			*res;

	if (fd == -1)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	size = read(fd, buffer, BUFFER_SIZE);
	if (size == -1)
	{
		free(buffer);
		return (NULL);
	}
	buffer[size] = '\0';
	if (ft_strchr(buffer, '\n') != NULL)
		delpos = ft_strchr(buffer, '\n') - buffer;
	else
		delpos = size;
	res = malloc(delpos);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, buffer, delpos);
	free(buffer);
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