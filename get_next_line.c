/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:32:36 by dchrysov          #+#    #+#             */
/*   Updated: 2024/10/26 16:16:36 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	ssize_t		bytes;
	static char	*buffer;
	char		*res;
	unsigned long			delpos;

	if (fd == -1)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes == -1)
	{
		free(buffer);
		return (NULL);
	}
	buffer[bytes] = '\0';
	while (ft_strnstr((const char)buffer, "\n", bytes) != NULL ||  ft_strnstr((const char)buffer, "\0", bytes) != NULL)
	{
		if (ft_strnstr((const char)buffer, "\n", bytes) != NULL)
		{
			res = ft_strnstr((const char)buffer, "\n", bytes);
			delpos = ft_strlen(buffer) - ft_strlen(res);
			ft_strlcpy(res, buffer, delpos + 1);
		}
	}
	return (res);
}

# include <fcntl.h>
int	main(void)
{
	// int		fd = open("/Users/dchrysov/francinette/tests/get_next_line/gnlTester/files/43_with_nl", O_RDONLY);
	char	*s;

	while ((s = get_next_line(0)) != NULL)
		printf("%s", s);
	// close(fd);
	return (0);
}
