/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:11:31 by dchrysov          #+#    #+#             */
/*   Updated: 2024/11/01 12:45:05 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	ssize_t		bytes;
	char		*temp;
	char		*buffer;
	char		*remainder;
	char		*line;

	if (fd == -1 || BUFFER_SIZE < 0)
		return (NULL);
	if (!temp)
	{
		temp = malloc(BUFFER_SIZE + 1);
		if (temp == NULL)
			return (NULL);
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes < 0)
			return (NULL);
		buffer = ft_strndup(temp, ft_strlen(temp));
		free(temp);
		temp = NULL;
	}

	if (buffer)
	{
		remainder = ft_strchr(buffer, '\n');
		line = ft_strndup(buffer, ft_strlen(remainder + 1));
		
	}

}

int	main(void)
{

}