/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils_02.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:19:16 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/20 22:44:50 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_redirection(char *token)
{
	return (!ft_strcmp(token, ">") || !ft_strcmp(token, "<")
		|| !ft_strcmp(token, ">>") || !ft_strcmp(token, "<<"));
}

static int	skip_redirection(char **tokens, int *index)
{
	if (is_redirection(tokens[*index]) && tokens[*index + 1])
	{
		(*index)++;
		return (1);
	}
	return (0);
}

char	*strip_redirections(char *command)
{
	char	**tokens;
	char	*stripped_cmd;
	char	*new_cmd;
	int		i;

	tokens = ft_split(command, ' ');
	if (!command || !tokens)
		return (NULL);
	stripped_cmd = NULL;
	i = -1;
	while (tokens[++i])
	{
		if (skip_redirection(tokens, &i))
			continue ;
		new_cmd = append_token(stripped_cmd, tokens[i]);
		free(stripped_cmd);
		stripped_cmd = new_cmd;
		if (stripped_cmd == NULL)
			break ;
	}
	free_array(tokens);
	return (stripped_cmd);
}
