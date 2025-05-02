/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:59:37 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/20 23:05:16 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*t1;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	t1 = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!t1)
		return (NULL);
	while (s1[i])
	{
		t1[i] = s1[i];
		i++;
	}
	t1[i] = '\0';
	return (t1);
}

char	*ft_substr(char *s, int start, size_t len)
{
	size_t	i;
	char	*t;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	if ((int)len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	t = malloc((len + 1) * sizeof(char));
	if (!t)
		return (NULL);
	while (s[start + i] && i < len)
	{
		t[i] = s[start + i];
		i++;
	}
	t[i] = '\0';
	return (t);
}

char	*ft_ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)s + i);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
