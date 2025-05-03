/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:18:14 by eelkabia          #+#    #+#             */
/*   Updated: 2025/05/03 16:34:53 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_child(char **s, t_utils *u, int pp[2], int np[2])
{
	setup_child_signals();
	if (u->i < u->nc - 1)
		close(np[0]);
	if (u->i > 0)
	{
		dup2(pp[0], STDIN_FILENO);
		close(pp[0]);
		close(pp[1]);
	}
	if (u->i < u->nc - 1)
	{
		dup2(np[1], STDOUT_FILENO);
		close(np[1]);
		close(np[0]);
	}
	ft_process(s[u->i], NULL, 0, u);
	exit(u->dir->exit_status_);
}

void	handle_parent(int pp[2], int np[2], int i, int nc)
{
	if (i > 0)
	{
		close(pp[0]);
		close(pp[1]);
	}
	if (i < nc - 1)
	{
		pp[0] = np[0];
		pp[1] = np[1];
	}
}

void	close_pipes(int pp[2])
{
	close(pp[0]);
	close(pp[1]);
}

static void	setup_child_io(int pp[2], int np[2], t_utils *u)
{
	setup_child_signals();
	if (u->i < u->nc - 1)
		close(np[0]);
	if (u->i > 0)
	{
		dup2(pp[0], STDIN_FILENO);
		close(pp[0]);
		close(pp[1]);
	}
	if (u->i < u->nc - 1)
	{
		dup2(np[1], STDOUT_FILENO);
		close(np[1]);
		close(np[0]);
	}
}

void	handle_child_process(char **s, t_utils *u, int pp[2], int np[2])
{

	setup_child_io(pp, np, u);
	ft_process(s[u->i], NULL, 0, u);
	exit(u->dir->exit_status_);
}
