/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:06:10 by eelkabia          #+#    #+#             */
/*   Updated: 2025/05/02 12:35:24 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_valid_long(char *str)
{
	char	*max_long;
	char	*min_long;
	size_t		len;

	max_long = "9223372036854775807";
	min_long = "-9223372036854775808";
	if (!str)
		return (0);
	len = ft_strlen(str);
	if (*str != '-' && (len > 19 || (len == 19 && ft_strcmp(str, max_long) > 0)))
		return (0);
	if (*str == '-' && (len > 20 || (len == 20 && ft_strcmp(str, min_long) > 0)))
		return (0);
	return (1);
}

void	handle_exit(char **split, t_dir *directory, t_stat *STATUS)
{
	*STATUS = 1;
	directory->exit_status_ = 0;
	if (split[1] && split[2])
	{
		write(1, "exit\n✘ mish: exit: too many arguments\n", 41);
		directory->exit_status_ = 1;
		*STATUS = 0;
	}
	else if (split[1] && ((is_num(split[1]) && !ft_atoi(split[1]))
			|| (nested_quotes(split[1]) == 2)))
	{
		printf("exit\n✘ mish: exit: %s: numeric argument required\n", split[1]);
		directory->exit_status_ = 2;
	}
	else if (split[1] && !is_valid_long(split[1]))
	{
		printf("exit\n✘ mish: exit: %s: numeric argument required\n", split[1]);
		directory->exit_status_ = 2;
	}
	else
		safe_exit(split, directory);
}

static void	handle_builtins(char *line, char **split, t_utils *u)
{
	if (!(line[0] == '\0' || !split || !split[0]))
	{
		if (!ft_strcmp(split[0], "env"))
			parse_env(*u->env, 0, u->dir);
		else if (!ft_strcmp(split[0], "pwd"))
		{
			printf("%s\n", u->dir->dir);
			u->dir->exit_status_ = 0;
		}
	}
}

int	is_builtin(char **args)
{
	if (!args[0])
		return (0);
	if (!ft_strncmp(args[0], "env", 4))
		return (1);
	if (!ft_strncmp(args[0], "pwd", 4))
		return (1);
	return (0);
}

int	try_builtin(char **args, t_utils *u)
{
	if (is_builtin(args))
	{
		handle_builtins(args[0], args, u);
		return (1);
	}
	return (0);
}
