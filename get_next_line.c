/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:11:31 by dchrysov          #+#    #+#             */
/*   Updated: 2024/11/04 17:26:55 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief frees and reallocates sz bytes for the buff and then assigns it the value of temp + app_str 
 * 
 * @param buff the buffer to be resized and reassigned.
 * @param sz the size of the buffer to fit the values of both the temp and app_str.
 * @param temp copying of its value to the buffer.
 * @param app_str appending its value to the buffer.
 * 
 * @returns the buffer variable after resizing and reassigning.
 */
static char	*buffer_append(char *buff, char *temp, char *app_str, int sz)
{
	temp = ft_strndup(buff, ft_strlen(buff));
	free(buff);
	buff = malloc(sz);
	if (buff == NULL)
		return (NULL);
	ft_strlcpy(buff, temp, ft_strlen(temp) + 1);
	ft_strlcat(buff, app_str, sz + 1);
	free(temp);
	return (buff);
}

/**
 * @brief Manual implementation of the official getline command.
 * 
 * @param append_bytes The size of the buffer,
 * @param to_append Appends <=BUFFER_SIZE data to the buffer.
 * @param buffer The main buffer, which is searched for the \\n, 
 * after each repetition of the while loop.
 * @param temp Used to temporarily store the value of buffer, before its resizing.
 * @param line Contains data written up to the \\n found in the buffer.
 * 
 * @returns The string contained in the variable named line.
 */
char	*get_next_line(int fd)
{
	ssize_t		append_bytes;
	ssize_t		total_size;
	static char	*buffer;
	char		to_append[BUFFER_SIZE + 1];
	char		*temp;
	char		*line;
	char		*delpos;

	if (fd == -1 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	append_bytes = read(fd, to_append, BUFFER_SIZE);
	if (append_bytes < 0)
		return (NULL);
	to_append[append_bytes] = '\0';
	total_size = append_bytes;
	temp = NULL;
	delpos = NULL;
	if (buffer && *buffer)
	{
		if (append_bytes != 0)								// buff is not empty and there are still data to read
		{
			total_size += ft_strlen(buffer);
			buffer = buffer_append(buffer, temp, to_append, total_size);
		}
	}
	else
	{
		if (append_bytes == 0)							// the buff is empty and there are no data left to read
			return (NULL);
		buffer = ft_strndup(to_append, ft_strlen(to_append));		// initialization of buff
	}
	while (1)
	{
		delpos = ft_strchr(buffer, '\n');
		if (delpos)
		{
			delpos++;
			temp = ft_strndup(delpos, ft_strlen(delpos));
			line = ft_strndup(buffer, ft_strlen(buffer) - ft_strlen(delpos));
			free (buffer);
			buffer = ft_strndup(temp, ft_strlen(temp));
			delpos = NULL;
			free(temp);
			temp = NULL;
			return (line);
		}
		append_bytes = read(fd, to_append, BUFFER_SIZE);
		if (append_bytes < 0)
			return (NULL);
		to_append[append_bytes] = '\0';
		total_size += append_bytes;
		if (append_bytes == 0)
		{
			if (buffer && *buffer)
			{
				line = ft_strndup(buffer, ft_strlen(buffer));
				buffer = NULL;
				return (line);
			}
			return (NULL);
		}
		buffer = buffer_append(buffer, temp, to_append, total_size);
	}
	free(temp);
	temp = NULL;
	return (NULL);
}

// #include <stdio.h>
// #include <fcntl.h>
// int	main(void)
// {
// 	// int		fd = open("/home/dimitris/francinette/tests/get_next_line/fsoares/only_nl.txt", O_RDONLY);
// 	int		fd = open("/Users/dchrysov/francinette/tests/get_next_line/fsoares/only_nl.txt", O_RDONLY);
// 	char	*s;

// 	// printf("%s", get_next_line(fd));
// 	while ((s = get_next_line(fd)) != NULL)
// 		printf("%s", s);
// 	return (0);
// }
