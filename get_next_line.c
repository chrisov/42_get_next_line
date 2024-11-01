/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:11:31 by dchrysov          #+#    #+#             */
/*   Updated: 2024/11/01 17:13:08 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief Manual implementation of the official getnextline command.
 * @note Remainder buffer and line are the ony mem allocated variables that need freeing.
 * @param bytes The size of the buffer, as indicated by the BUFFER_SIZE variable.
 * @param temp Temporary buffer that the whole content written to the descriptor.
 * @param buffer The main buffer variable, initialized as temp and from which remainder is extracted.
 * @param line The return value when there is content written to the descriptor.
 * @returns The string contained in the variable named line.
 */
char	*get_next_line(int fd)
{
	ssize_t		bytes;
	static char	*remainder;
	static char	*buffer;
	char		*line;
	char		*delpos;

	if (fd == -1 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (buffer == NULL)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return (NULL);
	}
	if (remainder == NULL)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
		{
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		buffer[bytes] = '\0';
	}
	delpos = ft_strchr(buffer, '\n');
	if (delpos)
	{
		line = ft_strndup(buffer, ft_strlen(delpos) - ft_strlen(buffer) + 1);
		remainder = ft_strndup(delpos + 1, ft_strlen(delpos + 1));
		free (buffer);
		buffer = NULL;
		return (line);
	}
	else
	{
		if (buffer && *buffer)
		{
			line = ft_strndup(buffer, ft_strlen(buffer));
			free(buffer);
			buffer = NULL;
			return (line);
		}
	}
	return (NULL);
}
// #include <fcntl.h>
// #include <stdio.h>
// int	main(void)
// {
// 	// int		fd = open("/home/dimitris/francinette/tests/get_next_line/gnlTester/files/multiple_line_with_nl", O_RDONLY);
// 	int		fd = open("/Users/dchrysov/francinette/tests/get_next_line/fsoares/lines_around_10.txt", O_RDONLY);
// 	char	*s;

// 	// s = NULL;
// 	// read(fd, s, BUFFER_SIZE);
// 	// printf("\"%s\"\n", s);

// 	while ((s = get_next_line(fd)) != NULL)
// 		printf("\"%s\"\n", s);
// 	return (0);
// }