/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitris <dimitris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:11:31 by dchrysov          #+#    #+#             */
/*   Updated: 2024/11/04 01:00:40 by dimitris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

/**
 * @brief Manual implementation of the official getline command.
 * 
 * @note The 1char edge case needs special treatment, using char instead of *char.
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
	char		to_append[BUFFER_SIZE];
	char		*temp;
	static char	*buffer;
	char		*line;
	char		*delpos;

	if (fd == -1 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	append_bytes = read(fd, to_append, BUFFER_SIZE);
	if (append_bytes < 0)
		return (NULL);
	to_append[append_bytes] = '\0';
	total_size = append_bytes;
	if (buffer == NULL)
	{
		if (append_bytes == 0)
			return (NULL);
		buffer = ft_strndup(to_append, ft_strlen(to_append));
	}
	else
	{
		if (append_bytes != 0)
		{
			total_size += ft_strlen(buffer);
			temp = ft_strndup(buffer, ft_strlen(buffer));
			free(buffer);
			buffer = malloc(total_size);
			if (buffer == NULL)
				return (NULL);
			ft_strlcpy(buffer, temp, ft_strlen(temp) + 1);
			ft_strlcat(buffer, to_append, total_size + 1);
		}
		else
		{
			line = ft_strndup(buffer, ft_strlen(buffer));
			free(buffer);
			buffer = NULL;
			return (line);
		}
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
			return (free(temp), line);
		}
		append_bytes = read(fd, to_append, BUFFER_SIZE);
		if (append_bytes <= 0)
			return (NULL);
		to_append[append_bytes] = '\0';
		total_size += append_bytes;
		temp = ft_strndup(buffer, ft_strlen(buffer));
		free(buffer);
		buffer = malloc(total_size);
		if (buffer == NULL)
			return (NULL);
		ft_strlcpy(buffer, temp, ft_strlen(temp) + 1);
		ft_strlcat(buffer, to_append, total_size +1);
		free(temp);
	}
	free(temp);
	temp = NULL;
	return (NULL);
}

// #include <fcntl.h>
// int	main(void)
// {
// 	int		fd = open("/home/dimitris/francinette/tests/get_next_line/fsoares/only_nl.txt", O_RDONLY);
// 	// int		fd = open("/Users/dchrysov/francinette/tests/get_next_line/fsoares/lines_around_10.txt", O_RDONLY);
// 	char	*s;

// 	// printf("%s", get_next_line(fd));
// 	while ((s = get_next_line(fd)) != NULL)
// 		printf("%s", s);
// 	return (0);
// }
