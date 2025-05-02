/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:08:49 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/20 23:01:50 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_global = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(t_signal *config)
{
	config->sa_int.sa_handler = handle_sigint;
	sigemptyset(&config->sa_int.sa_mask);
	config->sa_int.sa_flags = 0;
	sigaction(SIGINT, &config->sa_int, NULL);
	config->sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&config->sa_quit.sa_mask);
	config->sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &config->sa_quit, NULL);
}

int	handle_signals(int status, int fd, char **tokens)
{
	if (WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGQUIT)
	{
		close(fd);
		free_array(tokens);
		return (1);
	}
	return (0);
}
