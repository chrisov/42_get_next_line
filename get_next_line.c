/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitris <dimitris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:11:31 by dchrysov          #+#    #+#             */
/*   Updated: 2024/11/02 01:11:17 by dimitris         ###   ########.fr       */
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
	static char	*delpos;

	if (fd == -1 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	// if (BUFFER_SIZE == 1)
	// {

	// }
	append_bytes = read(fd, to_append, BUFFER_SIZE);
	if (append_bytes <= 0)
		return (NULL);
	if (!delpos)
	{
		buffer = ft_strndup(to_append, ft_strlen(to_append));
		total_size = append_bytes;
	}
	else
	{
		temp = ft_strndup(buffer, ft_strlen(buffer));
		total_size = ft_strlen(temp) + BUFFER_SIZE + 1;
		free(buffer);
		buffer = malloc(total_size);
		if (!buffer)
			return (NULL);
		ft_strlcpy(buffer, temp, total_size + 1);
		ft_strlcat(buffer, to_append, total_size + 1);
	}
	while (1)
	{
		delpos = ft_strchr(buffer, '\n');
		if (delpos)
		{
			delpos++;
			line = ft_strndup(buffer, ft_strlen(buffer) - ft_strlen(delpos));
			ft_strlcpy(buffer, delpos, ft_strlen(delpos) + 1);
			return (free(temp), line);
		}
		append_bytes = read(fd, to_append, BUFFER_SIZE);
		if (append_bytes <= 0)
			return (NULL);
		if (append_bytes <= BUFFER_SIZE)
		{
			total_size += append_bytes;
			temp = ft_strndup(buffer, ft_strlen(buffer));
			free(buffer);
			buffer = malloc(total_size + 1);
			if (!buffer)
				return (NULL);
			ft_strlcpy(buffer, temp, total_size + 1);
			ft_strlcat(buffer, to_append, total_size + 1);
		}
	}
	return (free(temp), free(buffer), free(line), NULL);
}

// static char	*one_char_buf(int fd)
// {
// 	ssize_t	bytes;
// 	char	c;
// 	char	*str;
// 	char	*temp;

// 	bytes = read(fd, &c, 1);
// 	if (!str)
// 	{
// 		str = malloc(2);
// 		ft_strlcpy(str, c, 2);
// 	}


// }


#include <fcntl.h>
int	main(void)
{
	int		fd = open("/home/dimitris/francinette/tests/get_next_line/fsoares/lines_around_10.txt", O_RDONLY);
	// int		fd = open("/Users/dchrysov/francinette/tests/get_next_line/fsoares/lines_around_10.txt", O_RDONLY);
	char	*s;

	// s = malloc(43);
	// while ((bytes = read(fd, s, 2)) > 0)
	// 	printf("%s", s);
	// s[43] = '\0';

	// printf("%s", get_next_line(fd));
	while ((s = get_next_line(fd)) != NULL)
		printf("%s", s);
	// printf("\"%s\"\n", get_next_line(fd));
	return (0);
}
