/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:02:39 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/24 21:13:32 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	add_env_node(t_env **lst, t_env **curr, char *env_str)
{
	t_env	*new;

	new = create_node(env_str);
	if (!new)
		return (0);
	if (!*lst)
	{
		*lst = new;
		*curr = *lst;
	}
	else
	{
		(*curr)->next = new;
		*curr = (*curr)->next;
	}
	return (1);
}

t_env	*create_env(char **envp)
{
	t_env	*lst;
	t_env	*curr;
	int		i;
	int		has_home;

	lst = NULL;
	has_home = 0;
	i = -1;
	if (!envp)
		return (NULL);
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "HOME=", 6))
			has_home = 1;
		if (!add_env_node(&lst, &curr, envp[i]))
			printf("Warning: Failed to create node for: %s\n", envp[i]);
	}
	if (!has_home && !add_env_node(&lst, &curr, "HOME=/home/izahr"))
		printf("Warning: Failed to create HOME node\n");
	return (lst);
}

void	parse_env(t_env *lst, int k, t_dir *dir)
{
	if (!lst)
	{
		write(1, "There is No Environement Variables. . .\n", 41);
		exit(1);
	}
	while (lst)
	{
		if (k == 0)
			printf("%s=%s\n", lst->var, lst->value);
		else
			printf("declare -x %s=\"%s\"\n", lst->var, lst->value);
		lst = lst->next;
	}
	dir->exit_status_ = 0;
}

void	remove_middle(t_env *tmp, t_env *current)
{
	tmp->next = current->next;
	free(current->var);
	free(current->value);
	free(current);
}

t_env	*clear_node(t_env *env, char *str)
{
	t_env	*current;
	t_env	*tmp;

	current = env;
	tmp = NULL;
	if (!env || !str)
		return (env);
	if (current && !ft_strcmp(current->var, str))
	{
		env = current->next;
		free(current->var);
		free(current->value);
		free(current);
		return (env);
	}
	while (current && ft_strcmp(current->var, str))
	{
		tmp = current;
		current = current->next;
	}
	if (current)
		remove_middle(tmp, current);
	return (env);
}
