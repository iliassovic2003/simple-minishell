/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_join_utils_03.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:24:34 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/20 22:53:06 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

void	append_str(const char *src, char *dest, size_t *j)
{
	size_t	k;

	k = 0;
	while (src[k])
		dest[(*j)++] = src[k++];
}

char	*append_token(char *current_cmd, char *token_to_add)
{
	char	*space_added;
	char	*result;

	if (!current_cmd)
		return (ft_strdup(token_to_add));
	space_added = ft_strjoin(current_cmd, " ");
	if (!space_added)
		return (NULL);
	result = ft_strjoin(space_added, token_to_add);
	free(space_added);
	return (result);
}

void	normal_cmd(char **tokens, int i, char **new_cmd, char **tmp)
{
	char	*space_joined;
	char	*token_joined;

	space_joined = ft_strjoin(*new_cmd, " ");
	if (!space_joined)
	{
		free(*new_cmd);
		*new_cmd = NULL;
		return ;
	}
	free(*tmp);
	*tmp = space_joined;
	token_joined = ft_strjoin(*tmp, tokens[i]);
	if (!token_joined)
	{
		free(*tmp);
		*new_cmd = NULL;
		return ;
	}
	free(*tmp);
	*new_cmd = token_joined;
}
