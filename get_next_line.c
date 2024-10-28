/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:32:36 by dchrysov          #+#    #+#             */
/*   Updated: 2024/10/28 18:14:11 by dchrysov         ###   ########.fr       */
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

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	printf("\nbuffer: \"%s\"\n", buffer);
	while (1)
	{
		printf("\nremainder: \"%s\"\n", remainder);
		// if (ft_strncmp(buffer, "", ft_strlen(buffer)) == 0 && remainder != NULL)
		// 	buffer = remainder;
		if (remainder)
		{
			printf("\nbuffer before: \"%s\"\n", buffer);
			remainder = ft_strnstr(buffer, "\n", ft_strlen(buffer));
			remainder++;
			line = ft_strndup(buffer, ft_strlen(buffer) - ft_strlen(remainder));
			// ft_memmove(buffer, remainder + 1, ft_strlen(remainder - 2));
			// buffer[ft_strlen(remainder)] = '\0';
			// printf("\nbuffer: \"%s\"\n", buffer);
			// printf("\n\nremainder: \"%s\"\n\n", remainder);
			return (line);
		}
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
		{
			if (remainder && *remainder)
			{
				line = ft_strndup(remainder, ft_strlen(remainder));
				remainder = NULL;
				return (line);
			}
			return (NULL);
		}
		buffer[bytes] = '\0';
		remainder = ft_strjoin(remainder, buffer);
	}
}

# include <fcntl.h>
int	main(void)
{
	// int		fd = open("/home/dimitris/francinette/tests/get_next_line/gnlTester/files/multiple_line_with_nl", O_RDONLY);
	int		fd = open("/Users/dchrysov/francinette/tests/get_next_line/gnlTester/files/multiple_line_with_nl", O_RDONLY);
	char	*s;
	int		i = 1;

	while ((s = get_next_line(fd)) != NULL)
		printf("\nline[%d]: \"%s\"\n", i++, s);
	// printf("\nline[%d]: \"%s\"\n", i++, get_next_line(fd));
	// printf("\nline[%d]: \"%s\"\n", i++, s);
	close(fd);
	return (0);
}
