/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:20:53 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/20 23:15:42 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*find_value_env(char *key, t_env **head)
{
	t_env	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (ft_strlen(key) == ft_strlen(temp->var) && ft_strncmp(key, temp->var,
				ft_strlen(key)) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

static char	*get_full_path(t_env *head)
{
	return (find_value_env("PATH", &head));
}

static char	*path_join(char *cmd, char *part_path)
{
	char	*path;
	char	*tmp;

	tmp = ft_strjoin(part_path, "/");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (path);
}

char	*get_path(char *cmd, t_env *env)
{
	char	**path_argv;
	char	*path_dir;
	char	*path;
	int		i;

	path_dir = get_full_path(env);
	if (!path_dir)
		return (NULL);
	path_argv = ft_split(path_dir, ':');
	if (!path_argv)
		return (NULL);
	i = 0;
	while (path_argv[i])
	{
		path = path_join(cmd, path_argv[i]);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	free_array(path_argv);
	return (NULL);
}
