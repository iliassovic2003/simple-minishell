/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_02.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:59:37 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/20 23:05:05 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!src)
		src = "";
	if (!dst)
		return (0);
	while (src[i])
		i++;
	if (dstsize == 0)
		return (i);
	while (src[j] && j < dstsize - 1)
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	cc;

	i = 0;
	cc = (unsigned char)c;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)(s + i));
		i++;
	}
	if (!cc)
		return ((char *)(s + i));
	return (NULL);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			x;
	unsigned char	*dstt;
	unsigned char	*srcc;

	x = 0;
	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return ((void *)src);
	if (n == 0)
		return (dst);
	dstt = (unsigned char *)dst;
	srcc = (unsigned char *)src;
	while (x < n)
	{
		dstt[x] = srcc[x];
		x++;
	}
	return (dst);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
