/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:01:26 by dchrysov          #+#    #+#             */
/*   Updated: 2024/11/04 17:23:54 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

unsigned long	ft_strlen(const char str[])
{
	const char		*ptr;
	unsigned long	len;

	ptr = str;
	len = 0;
	if (str == NULL)
		return (0);
	while (*ptr)
	{
		len++;
		ptr++;
	}
	return (len);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char			*d;
	const unsigned char		*s;
	size_t					i;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	if (d == NULL && s == NULL)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char	*ft_strndup(const char *s, unsigned long size)
{
	char			*ptr;
	unsigned long	len;

	len = ft_strlen(s);
	if (size <= ft_strlen(s))
		len = size;
	ptr = malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, s, len);
	ptr[len] = '\0';
	return (ptr);
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

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	cat_len;
	size_t	i;

	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	cat_len = ft_strlen(dst);
	i = 0;
	while (src[i] != '\0' && cat_len < dstsize - 1)
	{
		dst[cat_len] = src[i];
		cat_len++;
		i++;
	}
	dst[cat_len] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}

char	*ft_strchr(const char *s, int c)
{
        while (*s)
        {
                if (*s == c)
                        return ((char *)s);
                s++;
        }
        if (*s == c)
                return ((char *)s);
        return (NULL);
}
