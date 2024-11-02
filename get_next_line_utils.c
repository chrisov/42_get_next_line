/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitris <dimitris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:01:26 by dchrysov          #+#    #+#             */
/*   Updated: 2024/11/02 00:45:28 by dimitris         ###   ########.fr       */
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

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char			*d;
	const unsigned char		*s;
	size_t					i;

	i = 0;
	s = (const unsigned char *)src;
	d = (unsigned char *)dst;
	if (d == NULL && s == NULL)
		return (NULL);
	while (i < len)
	{
		if (d < s)
		{
			d[i] = s[i];
			i++;
		}
		else
		{
			d[len - i - 1] = s[len - i - 1];
			i ++;
		}
	}
	return (dst);
}

char	*ft_strndup(const char *s, unsigned long size)
{
	char			*ptr;
	unsigned long	len;

	if (size <= ft_strlen(s))
		len = size;
	else
		len = ft_strlen(s);
	ptr = malloc(len * sizeof(char) + 1);
	if (ptr == NULL)
		return (NULL);
	ft_memmove(ptr, s, (size_t)len);
	ptr[len] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*concat_str;

	concat_str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (concat_str == NULL)
		return (NULL);
	ft_strlcpy(concat_str, s1, ft_strlen(s1) + 1);
	ft_strlcat(concat_str, s2, ft_strlen(concat_str) + ft_strlen(s2) + 1);
	return (concat_str);
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && n--)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	return (0);
}

char    *ft_strchr(const char *s, int c)
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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

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
