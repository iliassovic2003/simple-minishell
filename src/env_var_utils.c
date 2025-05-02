/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:39:47 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/20 18:17:01 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_user(const char *user)
{
	char	path[256];

	ft_strcpy(path, "/home/");
	ft_strcat(path, user);
	if (access(path, F_OK) == 0)
		return (ft_strdup(path));
	return (NULL);
}

static int	is_valid_var_char(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0'
			&& c <= '9') || c == '_');
}

static void	handle_special_cases(const char *t, t_tmp *tmp, int st)
{
	char	exit_num[12];

	if (t[tmp->i] == '?')
	{
		int_to_str(st, exit_num);
		append_str(exit_num, tmp->result, &tmp->j);
		tmp->i++;
	}
	else if (t[tmp->i] == '0')
	{
		append_str("mish", tmp->result, &tmp->j);
		tmp->i++;
	}
}

static void	handle_env_vars(const char *t, t_tmp *tmp, t_env *env)
{
	size_t	var_start;
	char	*var_name;
	char	*env_val;

	var_start = tmp->i;
	while (t[tmp->i] && is_valid_var_char(t[tmp->i]))
		tmp->i++;
	var_name = malloc(tmp->i - var_start + 1);
	if (!var_name)
		return ;
	ft_strlcpy(var_name, t + var_start, tmp->i - var_start + 1);
	env_val = check_env(env, var_name);
	free(var_name);
	if (env_val)
		append_str(env_val, tmp->result, &tmp->j);
}

void	handle_dollar(const char *t, t_tmp *tmp, t_env *env, int st)
{
	tmp->i++;
	if (t[tmp->i] == '?' || t[tmp->i] == '0')
		handle_special_cases(t, tmp, st);
	else if (!is_valid_var_char(t[tmp->i]))
	{
		while (t[tmp->i] == '"' || t[tmp->i] == '\'')
			tmp->i++;
	}
	else
		handle_env_vars(t, tmp, env);
}
