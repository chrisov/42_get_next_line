/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:11:31 by dchrysov          #+#    #+#             */
/*   Updated: 2024/11/05 19:12:28 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


/**
 * @brief When a del is found, it returns the buffer up to the \\n.
 * 
 * @param temp Stores the value of del temporarily.
 * @param result Same as buffer, up to and including the \\n.
 * 
 * @returns result
 */
static char	*line_found(char **buff, char *del)
{
	char	*temp;
	char	*result;

	del++;
	temp = ft_strndup(del, ft_strlen(del));
	result = ft_strndup(*buff, ft_strlen(*buff) - ft_strlen(temp));
	free(*buff);
	*buff = ft_strndup(temp, ft_strlen(temp));
	free(temp);
	temp = NULL;
	return (result);
}

/**
 * @brief frees and reallocates sz bytes for the buff and 
 * then assigns it the value of temp + app_str 
 * 
 * @param buff the buffer to be resized and reassigned.
 * @param sz the size of the buffer to fit the values of
 * both the temp and app_str.
 * @param temp copying of its value to the buffer.
 * @param app_str appending its value to the buffer.
 * 
 * @returns the buffer variable after resizing and reassigning.
 */
static char	*buffer_append(char **buff, char *app_str, int sz)
{
	char	*temp;

	temp = ft_strndup(*buff, ft_strlen(*buff));
	free(*buff);
	*buff = malloc(sz + 1);
	if (*buff == NULL)
	{
		free(temp);
		return (NULL);
	}
	ft_strlcpy(*buff, temp, ft_strlen(temp) + 1);
	ft_strlcat(*buff, app_str, sz + 1);
	free(temp);
	return (*buff);
}

/**
 * @brief Manual implementation of the official getline command.
 * 
 * @param append_bytes The size of the buffer,
 * @param to_append Appends <=BUFFER_SIZE data to the buffer.
 * @param buffer The main buffer, which is searched for the \\n, 
 * after each repetition of the while loop.
 * @param temp Used to temporarily store the value of buffer, before 
 * its resizing.
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
	char		*line;
	char		*delpos;

	if (fd == -1 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	append_bytes = read(fd, to_append, BUFFER_SIZE);
	if (append_bytes < 0)
		return (NULL);
	if (append_bytes == 0)
	{
		if (!(buffer && *buffer))
			return (NULL);
		else
		{
			line = ft_strndup(buffer, ft_strlen(buffer));
			buffer = NULL;
			return (line);
		}
	}
	total_size = append_bytes;
	if (buffer != NULL)
		buffer = buffer_append(&buffer, to_append, total_size);
	else
		buffer = ft_strndup(to_append, ft_strlen(to_append));
	delpos = ft_strchr(buffer, '\n');
	while (!delpos)
	{
		append_bytes = read(fd, to_append, BUFFER_SIZE);
		if (append_bytes < 0)
			return (NULL);
		if (append_bytes == 0)
		{
			line = ft_strndup(buffer, ft_strlen(buffer));
			buffer = NULL;
			return (line);
		}
		total_size += append_bytes;
		buffer = buffer_append(&buffer, to_append, total_size);
		delpos = ft_strchr(buffer, '\n');
	}
	return (line_found(&buffer, delpos));
}

// #include <stdio.h>
// #include <fcntl.h>
// int	main(void)
// {
// 	// int		fd = open("/home/dimitris/francinette/tests/get_next_line/fsoares/lines_around_10.txt", O_RDONLY);
// 	// int		fd = open("/Users/dchrysov/francinette/tests/get_next_line/fsoares/lines_around_10.txt", O_RDONLY);
// 	int		fd = open("/Users/dchrysov/francinette/tests/get_next_line/fsoares/variable_nls.txt", O_RDONLY);
// 	char	*s;

// 	// printf("%s", get_next_line(fd));
// 	while ((s = get_next_line(fd)) != NULL)
// 		printf("\"%s\'", s);
// 	return (0);
// }
