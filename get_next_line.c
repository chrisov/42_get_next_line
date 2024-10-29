/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitris <dimitris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:32:36 by dchrysov          #+#    #+#             */
/*   Updated: 2024/10/29 01:08:41 by dimitris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	ssize_t			bytes;
	char			*buffer;
	char			*line;
	static char		*remainder;
	char			*delpos;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = NULL;
	while (1)
	{
		if (remainder)
		{
			delpos = ft_strnstr(remainder, "\n", ft_strlen(remainder));
			if (delpos)
			{
				line = ft_strndup(remainder, ft_strlen(remainder) - ft_strlen(delpos) + 1);
				remainder = ft_strndup(delpos + 1, ft_strlen(delpos) - 1);
				return (line);
			}
		}
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return (NULL);
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
		{
			if (remainder && *remainder)
			{
				line = ft_strndup(remainder, ft_strlen(remainder) - ft_strlen(delpos) + 1);
				free(remainder);
				remainder = NULL;
				return (line);
			}
			return (free(buffer), NULL);
		}
		buffer[bytes] = '\0';
		remainder = ft_strjoin(remainder, buffer);
	}
}

// # include <fcntl.h>
// int	main(void)
// {
// 	int		fd = open("/home/dimitris/francinette/tests/get_next_line/gnlTester/files/multiple_line_with_nl", O_RDONLY);
// 	// int		fd = open("/Users/dchrysov/francinette/tests/get_next_line/gnlTester/files/multiple_line_with_nl", O_RDONLY);
// 	char	*s;
// 	int		i = 1;

// 	while ((s = get_next_line(fd)) != NULL)
// 		printf("\nline[%d]: \"%s\"\n", i++, s);
// 	// printf("\nline[%d]: \"%s\"\n", i++, get_next_line(fd));
// 	// printf("\nline[%d]: \"%s\"\n", i++, s);
// 	close(fd);
// 	return (0);
// }
