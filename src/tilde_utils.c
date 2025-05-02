/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:56:36 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/20 23:10:49 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	safe_exit(char **split, t_dir *directory)
{
	printf("exit\n");
	if (split[1])
		directory->exit_status_ = ft_atoi(split[1]);
	if (split[1] && (ft_strlen(split[1]) == 20 && !ft_strcmp(split[1],
				"-9223372036854775808")))
		directory->exit_status_ = 0;
}

static char	*expand_home_dir(const char *token, const char *home_dir)
{
	char	*result;
	size_t	home_len;
	size_t	token_len;

	home_len = ft_strlen(home_dir);
	token_len = ft_strlen(token);
	result = malloc(home_len + token_len + 1);
	if (!result)
	{
		perror("malloc");
		return (NULL);
	}
	ft_strcpy(result, home_dir);
	if (token[1] == '/')
		ft_strcat(result, token + 1);
	return (result);
}

static char	*expand_user_dir(const char *token)
{
	char	*user;
	char	*user_home;

	user = ft_strdup(token + 1);
	if (!user)
		return (NULL);
	user_home = expand_user(user);
	free(user);
	return (user_home);
}

char	*expand_tilde(const char *token, t_dir dir)
{
	if (token[0] != '~')
		return (ft_strdup(token));
	if (token[1] == '/' || token[1] == '\0')
		return (expand_home_dir(token, dir.home));
	else
		return (expand_user_dir(token));
}
