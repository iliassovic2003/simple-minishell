/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:06:10 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/30 19:45:05 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_all_n(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-')
		return (1);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

static void	echo_while(char **args, int i, int len)
{
	int	j;

	while (args[i])
	{
		j = 0;
		if (!args[i][0])
		{
			i++;
			continue ;
		}
		len = ft_strlen(args[i]);
		while (j < len)
		{
			write(1, &args[i][j], 1);
			j++;
		}
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
}

void	handle_echo(char **args, t_dir *dir)
{
	int	i;
	int	line_flag;
	int	len;

	i = 1;
	len = 0;
	line_flag = 0;
	if (args[1] && (!ft_strcmp(args[1], "-n") || !is_all_n(args[1])))
	{
		line_flag = 1;
		i = 2;
	}
	echo_while(args, i, len);
	if (!line_flag)
		write(1, "\n", 1);
	dir->exit_status_ = 0;
}

void	handle_cd(char **split, t_env *my_env, t_dir *dir)
{
	if (!split[1])
		handle_cd_no_arg(my_env, dir);
	else if (!ft_strcmp(split[1], "-"))
		handle_cd_oldpwd(my_env, dir);
	else if (ft_strcmp(split[1], "-") && split[1][0] == '-')
	{
		printf("✘ mish: cd: %s: invalid option\n", split[1]);
		printf("cd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n");
	}
	else if (!split[2])
		handle_cd_path(split, my_env, dir);
	else
	{
		write(1, "✘ mish: cd: too many arguments\n", 33);
		dir->exit_status_ = 1;
	}
	update_directory(dir, my_env);
}

void	executing(t_utils *u)
{
	if (!ft_strcmp(u->split[0], "cd"))
		handle_cd(u->split, *(u->env), u->dir);
	else if (!ft_strcmp(u->split[0], "unset"))
	{
		u->dir->exit_status_ = 0;
		if (u->split[1])
			*u->env = clear_node(*u->env, u->split[1]);
	}
	else if (!ft_strcmp(u->split[0], "export"))
		handle_export(u->dir, u->split, *(u->env));
	else if (!ft_strcmp(u->split[0], "exit"))
		handle_exit(u->split, u->dir, u->status);
	else if (!ft_strcmp(u->split[0], "echo"))
		handle_echo(u->split, u->dir);
	else
		execve_input(u, u->split);
}
