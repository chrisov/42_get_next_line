/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:01:26 by dchrysov          #+#    #+#             */
/*   Updated: 2024/10/26 16:13:30 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	if (*little == '\0')
		return ((char *)big);
	while (*big && len >= ft_strlen(little))
	{
		if (*big == *little)
		{
			if (ft_strncmp(big, little, ft_strlen(little)) == 0)
				return ((char *)big);
		}
		big++;
		len--;
	}
	return (NULL);
}

unsigned long	ft_strlen(const char str[])
{
	const char		*ptr;
	unsigned long	len;

	ptr = str;
	len = 0;
	while (*ptr)
	{
		len++;
		ptr++;
	}
	return (len);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	cpy_len;

	i = 0;
	if (size <= 0)
		return (ft_strlen(src));
	if (size <= ft_strlen(src))
		cpy_len = size - 1;
	else
		cpy_len = ft_strlen(src);
	while (i < cpy_len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}
