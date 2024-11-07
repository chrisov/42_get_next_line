/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:11:31 by dchrysov          #+#    #+#             */
/*   Updated: 2024/11/07 15:45:50 by dchrysov         ###   ########.fr       */
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
static char	*line_found(char **buff, char *remainder)
{
	char	*temp;
	char	*result;

	temp = ft_strndup(remainder, ft_strlen(remainder));
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
	if (!*buff)
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

/**
 * @brief Searches the buffer for the \\n.
 * 
 * @param app_str Stores the data read from the fd.
 * @param bytes The bytes read from the fd.
 * @param result Stores the \\n pointer found in the buffer.
 *   
 * @returns Result.
 */
static char	*delim_search(int fd, char **buff, ssize_t size)
{
	ssize_t	bytes;
	char	*remainder;
	char	app_str[BUFFER_SIZE + 1];
	char	*result;

	remainder = ft_strchr(*buff, '\n');
	while (!remainder)
	{
		bytes = read(fd, app_str, BUFFER_SIZE);
		if (bytes < 0)
			return (NULL);
		if (bytes == 0)
		{
			result = ft_strndup(*buff, ft_strlen(*buff));
			free(*buff);
			*buff = NULL;
			return (result);
		}
		app_str[bytes] = '\0';
		size += bytes;
		*buff = buffer_append(buff, app_str, size);
		remainder = ft_strchr(*buff, '\n');
	}
	remainder++;
	return (line_found(&*buff, remainder));
}

static ssize_t	descriptor_read(int fd, char **buff, char *app_str)
{
	ssize_t	bytes;

	if (fd == -1 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		free(*buff);
		*buff = NULL;
		return (-1);
	}
	bytes = read(fd, app_str, BUFFER_SIZE);
	if (bytes < 0)
		return (-1);
	app_str[bytes] = '\0';
	return (bytes);
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
	static char	*buffer;
	char		to_append[BUFFER_SIZE + 1];

	append_bytes = descriptor_read(fd, &buffer, to_append);
	if (append_bytes < 0)
		return (NULL);
	if (!append_bytes)
	{
		if (buffer && *buffer)
			return (delim_search(fd, &buffer, append_bytes));
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		buffer = ft_strndup(to_append, ft_strlen(to_append));
	else
	{
		append_bytes += ft_strlen(buffer);
		buffer = buffer_append(&buffer, to_append, append_bytes);
	}
	return (delim_search(fd, &buffer, append_bytes));
}
