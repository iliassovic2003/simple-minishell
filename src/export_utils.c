/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:22:52 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/21 16:51:26 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_existant(t_env *my_env, char *str)
{
	t_env	*tmp;
	char	*str_key;
	char	*str_value;

	tmp = my_env;
	str_key = ft_substr(str, 0, ft_strchr(str, '=') - str);
	str_value = ft_strdup(ft_strchr(str, '=') + 1);
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, str_key))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(str_value);
			return (0);
		}
		tmp = tmp->next;
	}
	if (str_value)
		free(str_value);
	if (str_key)
		free(str_key);
	return (1);
}

static char	*join_export_args(char **split)
{
	char	*tmp;
	char	*new_tmp;
	int		i;

	tmp = ft_strdup(split[1]);
	if (!tmp)
		return (NULL);
	i = 2;
	while (split[i])
	{
		new_tmp = ft_strjoin(tmp, " ");
		free(tmp);
		if (!new_tmp)
			return (NULL);
		tmp = new_tmp;
		new_tmp = ft_strjoin(tmp, split[i]);
		free(tmp);
		if (!new_tmp)
			return (NULL);
		tmp = new_tmp;
		i++;
	}
	return (tmp);
}

static int	is_not_alpha_num_equal(char *str)
{
	int	danger_area;

	danger_area = 0;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str == '=')
			danger_area = 1;
		if (!((*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'Z')
				|| (*str >= 'a' && *str <= 'z') || *str == '_') && !danger_area)
			return (1);
		str++;
	}
	return (0);
}

void	handle_export(t_dir *directory, char **split, t_env *my_env)
{
	char	*tmp;
	int		is_invalid;
	int		is_allnum;

	directory->exit_status_ = 0;
	if (!split[1])
	{
		parse_env(my_env, -1, directory);
		return ;
	}
	tmp = join_export_args(split);
	if (!tmp)
		return ;
	is_invalid = is_not_alpha_num_equal(tmp);
	is_allnum = is_all_num(tmp);
	if (is_invalid || is_allnum)
	{
		printf("✘ mish: export: `%s': not a valid identifier\n", tmp);
		directory->exit_status_ = 1;
	}
	else if (!ft_strchr(tmp, '='))
		;
	else if (check_existant(my_env, tmp) == 1)
		ft_lstadd_back(&my_env, create_node(tmp));
	free(tmp);
}
