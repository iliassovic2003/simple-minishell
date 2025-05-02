/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:18:14 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/20 22:28:11 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	wait_children(int *cp, int nc, t_dir *d)
{
	int	i;
	int	status;

	i = -1;
	while (++i < nc)
	{
		if (cp[i] > 0)
		{
			waitpid(cp[i], &status, 0);
			if (i == nc - 1)
			{
				if (WIFEXITED(status))
					d->exit_status_ = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					d->exit_status_ = 128 + WTERMSIG(status);
			}
		}
	}
}

int	init_pipe_exec(int *nc, int **cp, char **split, t_dir *dir)
{
	*nc = 0;
	while (split[*nc])
		(*nc)++;
	*cp = malloc(*nc * sizeof(int));
	if (!*cp)
	{
		free_array(split);
		dir->exit_status_ = 1;
		return (0);
	}
	return (1);
}

void	init_sigactions(struct sigaction sa[3])
{
	sa[0].sa_handler = SIG_IGN;
	sigemptyset(&sa[0].sa_mask);
	sa[0].sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa[0], &sa[1]);
	sigaction(SIGQUIT, &sa[0], &sa[2]);
}

void	cleanup_pipe_exec(int *cp, char **split, struct sigaction sa[3])
{
	free(cp);
	free_array(split);
	sigaction(SIGINT, &sa[1], NULL);
	sigaction(SIGQUIT, &sa[2], NULL);
}
