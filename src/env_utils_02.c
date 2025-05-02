/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:02:39 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/20 22:05:37 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*check_env(t_env *env, char *str)
{
	t_env	*tmp;
	char	*var_name_end;
	char	saved_char;

	tmp = env;
	if (*str == '$')
		str++;
	if (*str == '\'' || *str == '"')
		str++;
	var_name_end = str;
	while (*var_name_end && *var_name_end != '\'' && *var_name_end != '"')
		var_name_end++;
	saved_char = *var_name_end;
	*var_name_end = '\0';
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, str))
		{
			*var_name_end = saved_char;
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	*var_name_end = saved_char;
	return (NULL);
}

t_env	*create_node(char *line)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	if (!line)
	{
		free(new_node);
		return (NULL);
	}
	if (ft_strchr(line, '='))
	{
		new_node->var = ft_substr(line, 0, ft_strchr(line, '=') - line);
		new_node->value = ft_strdup(ft_strchr(line, '=') + 1);
	}
	if (!new_node->var || !new_node->value)
	{
		free(new_node->var);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (!lst)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

static char	*create_env_entry(char *var, char *value)
{
	char	*entry;
	int		var_len;
	int		value_len;

	var_len = ft_strlen(var);
	value_len = ft_strlen(value);
	entry = malloc(var_len + value_len + 2);
	if (!entry)
		return (NULL);
	ft_strlcpy(entry, var, var_len + 1);
	entry[var_len] = '=';
	ft_strlcpy(entry + var_len + 1, value, value_len + 1);
	return (entry);
}

char	**convert_env(t_env *env)
{
	int		i;
	int		count;
	t_env	*tmp;
	char	**env_arr;

	count = 0;
	tmp = env;
	while (tmp && ++count)
		tmp = tmp->next;
	env_arr = malloc((count + 1) * sizeof(char *));
	if (!env_arr)
		return (NULL);
	i = -1;
	tmp = env;
	while (++i < count)
	{
		env_arr[i] = create_env_entry(tmp->var, tmp->value);
		if (!env_arr[i])
			return (NULL);
		tmp = tmp->next;
	}
	env_arr[count] = NULL;
	return (env_arr);
}
