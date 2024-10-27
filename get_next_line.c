/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitris <dimitris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:32:36 by dchrysov          #+#    #+#             */
/*   Updated: 2024/10/27 19:40:34 by dimitris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	ssize_t			bytes;
	static char		*buffer;
	char			*line;
	char			*remainder;
	unsigned int	i;

	i = 0;
	if (fd == -1 || BUFFER_SIZE <= 0)
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
	printf("\nbuffer: \"%s\" of len: %ld\n", buffer, strlen(buffer));
	remainder = strchr(buffer, '\n');
	if (remainder != NULL)
	{
		remainder++;
		printf("\nremainder: \"%s\" of len %ld\n", remainder, ft_strlen(remainder));
	}
	else
	{
		remainder = "";
		printf("\nremainder: \"%s\" of len %ld\n", remainder, ft_strlen(remainder));
	}
	line = malloc(ft_strlen(buffer) - ft_strlen(remainder) + 1);
	while (i < ft_strlen(buffer) - ft_strlen(remainder))
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	if (line == NULL)
		return (NULL);
	printf("\nline: \"%s\" of len %ld\n", line, ft_strlen(line));
	ft_memmove(buffer, remainder, ft_strlen(remainder) + 1);
	printf("\nThe new buffer: \"%s\" of len %ld\n", buffer, ft_strlen(buffer));
	return (line);
}

# include <fcntl.h>
int	main(void)
{
	// int		fd = open("/Users/dchrysov/francinette/tests/get_next_line/gnlTester/files/43_with_nl", O_RDONLY);
	// int		fd = open("/home/dimitris/francinette/tests/get_next_line/gnlTester/files/43_with_nl", O_RDONLY);
	// char	*s;

	// while ((s = get_next_line(fd)) != NULL)
	printf("\nReturn value of ft: \"%s\"\n\n", get_next_line(0));
	// printf("\nReturn value of ft: \"%s\"\n", get_next_line(fd));
	// close(fd);
	return (0);
}
