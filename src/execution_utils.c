/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:49:32 by eelkabia          #+#    #+#             */
/*   Updated: 2025/05/03 17:46:26 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_hundel(char **cmd, t_env *env)
{
	char	**env_arr;

	env_arr = convert_env(env);
	if (!env_arr)
		ft_perror("Memory allocation failed", 1);
	if (ft_ft_strchr(cmd[0], '/') != NULL)
	{
		if (execve(cmd[0], cmd, env_arr) == -1)
			ft_perror("Command execution failed", 126);
	}
	free_array(env_arr);
}

int	try_execute(char **args, t_env **env, t_dir *dir)
{
	char	*path;
	char	**env_arr;

	ft_hundel(args, *env);
	path = get_path(args[0], *env);
	if (!path)
	{
		ft_cmd("Command not found: ", args, 127);
		dir->exit_status_ = 127;
		return (1);
	}
	env_arr = convert_env(*env);
	//printf("heredoc_fd: %d\n", dir->heredoc_fd);
	if (dir->heredoc_fd > -1)
	{
		if (dup2(dir->heredoc_fd, STDIN_FILENO) == -1)
			perror("dup2");
		close(dir->heredoc_fd);
	}
	if (env_arr && execve(path, args, env_arr) == -1)
	{
		free(path);
		free_array(env_arr);
		ft_cmd("Execution failed: ", args, 126);
		dir->exit_status_ = 126;
	}
	free(path);
	free_array(env_arr);
	return (0);
}

void	parent_process(int *pipe_fd, int input_fd, t_utils *u, pid_t id)
{
	int	status;

	if (pipe_fd)
		close(pipe_fd[1]);
	if (input_fd != 0)
		close(input_fd);
	if (!pipe_fd)
	{
		waitpid(id, &status, 0);
		if (WIFEXITED(status))
			u->dir->exit_status_ = WEXITSTATUS(status);
	}
}
