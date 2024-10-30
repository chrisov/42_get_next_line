/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:32:36 by dchrysov          #+#    #+#             */
/*   Updated: 2024/10/30 18:10:22 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	ssize_t			bytes;
	char			buffer[BUFFER_SIZE + 1];
	char			*line;
	static char		*remainder;
	char			*delpos;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (remainder)
		{
			delpos = ft_strnstr(remainder, "\n", ft_strlen(remainder));
			if (delpos)
			{
				remainder = ft_strndup(delpos + 1, ft_strlen(delpos) - 1);
				line = ft_strndup(remainder, ft_strlen(remainder) - ft_strlen(delpos)+ 1);
				return (line);
			}
			free(delpos);
			delpos = NULL;
		}
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
		{
			if (remainder && *remainder)
			{
				line = ft_strndup(remainder, ft_strlen(remainder) - ft_strlen(delpos) + 1);
				free(remainder);
				remainder = NULL;		//this fixes the 1-line cases
				return (line);
			}
			// free(delpos);
			// delpos = NULL;
			return (NULL);
		}
		buffer[BUFFER_SIZE] = '\0';
		remainder = ft_strjoin(remainder, buffer);
	}
}

# include <fcntl.h>

int	main(void)
{
	// int		fd = open("/home/dimitris/francinette/tests/get_next_line/gnlTester/files/multiple_line_with_nl", O_RDONLY);
	int		fd = open("/Users/dchrysov/francinette/tests/get_next_line/fsoares/multiple_nl.txt", O_RDONLY);
	char	*s;

	while ((s = get_next_line(fd)) != NULL)
		printf("\"%s\"\n", s);
	close(fd);
	return (0);
}