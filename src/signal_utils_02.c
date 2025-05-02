/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils_02.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:08:49 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/20 23:02:15 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_sigquit(int sig)
{
	const char	*msg;

	(void)sig;
	msg = "Quit (core dumped)\n";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	exit(128 + SIGQUIT);
}

static void	handle_sigint_child(int sig)
{
	(void)sig;
	g_signal_global = 0;
	write(STDOUT_FILENO, "\n", 1);
	exit(128 + SIGINT);
}

void	setup_child_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint_child;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = handle_sigquit;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}
