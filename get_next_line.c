/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:32:36 by dchrysov          #+#    #+#             */
/*   Updated: 2024/10/24 18:54:46 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	ssize_t		bytesread;
	static char	*strread;
	static char	*res;
	// static char	*res_ptr;
	int			i;

	i = 0;
	strread = malloc(BUFFER_SIZE + 1);
	if (strread == NULL)
		return ("Error allocating memory");
	bytesread = read(fd, strread, BUFFER_SIZE);
	strread[bytesread] = '\0';
	while (*strread)
	{

	}
	free(strread);
	return (res);
}

int	main(void)
{
	char	*s;

	s = get_next_line(0);
	printf("str: %s", s);
	return (0);
}