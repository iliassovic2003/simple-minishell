/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:03:49 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/20 18:17:01 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	execute_command(char *cmd, t_utils *u)
{
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		u->dir->exit_status_ = 1;
		return ;
	}
	if (!args[0])
		u->dir->exit_status_ = 127;
	else if (!try_builtin(args, u))
		try_execute(args, u->env, u->dir);
	free_array(args);
}

void	execve_input(t_utils *u, char **split)
{
	int					nc;
	int					*cp;
	struct sigaction	sa[3];

	split = ft_split(*(u->line), '|');
	if (!split || !init_pipe_exec(&nc, &cp, split, u->dir))
		return ;
	init_sigactions(sa);
	execute_pipes(split, u, nc, cp);
	cleanup_pipe_exec(cp, split, sa);
}

void	ft_process(char *str, int *pipe_fd, int input_fd, t_utils *u)
{
	pid_t	id;
	char	*str_cmd;

	str_cmd = strip_redirections(str);
	id = fork();
	if (id == 0)
	{
		if (input_fd != 0)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (pipe_fd)
		{
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			close(pipe_fd[0]);
		}
		check_redirections(str);
		execute_command(str_cmd, u);
		exit(u->dir->exit_status_);
	}
	else if (id > 0)
		parent_process(pipe_fd, input_fd, u, id);
	free(str_cmd);
}
