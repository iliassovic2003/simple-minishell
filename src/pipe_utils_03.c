/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_03.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:18:14 by eelkabia          #+#    #+#             */
/*   Updated: 2025/05/03 16:37:11 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void update_parent_pipes(int pp[2], int np[2], t_utils *u)
{
	if (u->i > 0)
	{
		close(pp[0]);
		close(pp[1]);
	}
	if (u->i < u->nc - 1)
	{
		pp[0] = np[0];
		pp[1] = np[1];
	}
}

static int handle_pipe_creation(int np[2], t_utils *u)
{
	int pipe_result;

	if (u->i < u->nc - 1)
	{
		pipe_result = pipe(np);
		if (pipe_result < 0)
		{
			u->dir->exit_status_ = 1;
			perror("pipe");
			return (0);
		}
	}
	return (1);
}

static void pipe_init(int pp[2], t_utils *u, int nc)
{
	pp[0] = -1;
	pp[1] = -1;
	u->i = -1;
	u->nc = nc;
}

void execute_pipes(char **s, t_utils *u, int nc, int *cp)
{
	int pp[2];
	int np[2];
	int fork_result;

	pipe_init(pp, u, nc);
	u->dir->exit_status_ = 0;
	while (s[++(u->i)] && u->dir->exit_status_ == 0)
	{

		if (!handle_pipe_creation(np, u))
			break;
		fork_result = fork();
		if (fork_result == 0)
			handle_child_process(s, u, pp, np);
		else if (fork_result > 0)
			update_parent_pipes(pp, np, u);
		else
		{
			u->dir->exit_status_ = 1;
			perror("fork");
		}
		cp[u->i] = fork_result;
	}
	wait_children(cp, nc, u->dir);
	if (nc > 1)
		close_pipes(pp);
}
