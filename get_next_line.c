/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:11:31 by dchrysov          #+#    #+#             */
/*   Updated: 2024/11/05 20:32:11 by dchrysov         ###   ########.fr       */
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
 * @brief frees and then reallocates sz bytes of memory for 
 * the buff and then assigns the value of temp + app_str to it.
 * 
 * @param buff the buffer to be resized and reassigned.
 * @param sz the allocating size for the buffer.
 * @param temp copied to the buffer.
 * @param app_str appended to the buffer.
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
	temp = NULL;
	return (*buff);
}

static char	*delim_found(int fd, char **buff, ssize_t size)
{
	ssize_t	bytes;
	char	*del;
	char	app_str[BUFFER_SIZE + 1];
	char	*result;

	del = ft_strchr(*buff, '\n');
	while (!del)
	{
		bytes = read(fd, app_str, BUFFER_SIZE);
		app_str[bytes] = '\0';
		if (bytes < 0)
			return (NULL);
		if (bytes == 0)
		{
			result = ft_strndup(*buff, ft_strlen(*buff));
			*buff = NULL;
			return (result);
		}
		size += bytes;
		*buff = buffer_append(buff, app_str, size);
		del = ft_strchr(*buff, '\n');
	}
	return (line_found(&*buff, del));
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

	if (fd == -1 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	append_bytes = read(fd, to_append, BUFFER_SIZE);
	if (append_bytes < 0)
		return (NULL);
	to_append[append_bytes] = '\0';
	total_size = append_bytes;
	if (append_bytes == 0)
	{
		if (!(buffer && *buffer))											// eof and no buff (last step)
			return (NULL);
		else															// eof and still data to the buff (previously to last step)
			return(delim_found(fd, &buffer, total_size));
	}
	if (!buffer)														// no eof no data to the buffer (first step)
		buffer = ft_strndup(to_append, ft_strlen(to_append));
	else																// appending to_app to the already not empty buffer
		buffer = buffer_append(&buffer, to_append, append_bytes);
	return (delim_found(fd, &buffer, total_size));
}

#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	// int		fd = open("/home/dimitris/francinette/tests/get_next_line/fsoares/lines_around_10.txt", O_RDONLY);
	// int		fd = open("/Users/dchrysov/francinette/tests/get_next_line/fsoares/lines_around_10.txt", O_RDONLY);
	int		fd = open("/Users/dchrysov/francinette/tests/get_next_line/fsoares/read_error.txt", O_RDONLY);
	char	*s;

	// printf("%s", get_next_line(fd));
	while ((s = get_next_line(fd)) != NULL)
		printf("\"%s\'", s);
	return (0);
}
