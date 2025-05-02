/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_join_utils_02.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:24:34 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/20 22:58:32 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*handle_token_expansion(char *token, t_dir dir)
{
	char	*expanded;

	expanded = expand_tilde(token, dir);
	if (!expanded)
		expanded = ft_strdup(token);
	return (expanded);
}

static char	*join_with_space(char *line, char *token)
{
	char	*joined;
	char	*spaced;

	joined = ft_strjoin_free(line, token);
	if (!joined)
		return (NULL);
	spaced = ft_strjoin_free(joined, " ");
	return (spaced);
}

static char	*process_single_token(char *line, char *token, t_dir dir)
{
	char	*expanded;
	char	*new_line;

	expanded = handle_token_expansion(token, dir);
	if (!expanded)
		return (NULL);
	new_line = join_with_space(line, expanded);
	free(expanded);
	return (new_line);
}

static char	*remove_trailing_space(char *line)
{
	size_t	len;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0)
		line[len - 1] = '\0';
	return (line);
}

char	*build_new_line(char **tokens, t_dir dir)
{
	char	*new_line;
	char	*tmp;
	int		i;

	new_line = ft_strdup("");
	if (!new_line || !tokens)
		return (NULL);
	i = -1;
	while (tokens[++i])
	{
		tmp = process_single_token(new_line, tokens[i], dir);
		if (!tmp)
			return (free(new_line), NULL);
		new_line = tmp;
	}
	return (remove_trailing_space(new_line));
}
