/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:01:05 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/22 00:26:55 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_signal_global = 0;

void	init_main_vars(char **line, t_dir *dir, t_stat *status, char **av)
{
	(void)av;
	*line = NULL;
	dir->dir = NULL;
	dir->oldir = NULL;
	dir->home = NULL;
	dir->exit_status_ = 0;
	*status = 0;
}

void	handle_syntax_error(char **line, t_dir *dir)
{
	dir->exit_status_ = 1;
	free(*line);
	*line = NULL;
}

static void	cleanup_resources(t_dir *dir, t_env *env)
{
	if (dir->dir)
		free(dir->dir);
	if (dir->oldir)
		free(dir->oldir);
	if (dir->home)
		free(dir->home);
	lst_clean(env);
	rl_clear_history();
}

void	process_input(char **line, t_dir *dir, t_env **env, t_stat *status)
{
	t_utils	u;
	char	*expanded;

	u = (t_utils){line, NULL, env, dir, status, 0, 0};
	expanded = special_check(*line, *env, dir->exit_status_);
	if (expanded)
	{
		free(*line);
		*line = expanded;
	}
	u.split = parse_prompt_to_argv(*line);
	if ((*line)[0] == '\0' || !u.split || !u.split[0])
		dir->exit_status_ = 0;
	else
		executing(&u);
	if (*line)
		free(*line);
	if (u.split)
		free_array(u.split);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_signal	signal;
	t_dir		dir;
	t_stat		status;
	t_env		*my_env;

	(void)ac;
	init_main_vars(&line, &dir, &status, av);
	setup_signals(&signal);
	my_env = create_env(env);
	update_directory(&dir, my_env);
	while (!status)
	{
		line = readline("✧ mi/sh ➤ ");
		if (g_signal_global == SIGINT)
			dir.exit_status_ = 130;
		if (!line && printf("exit\n"))
			break ;
		if (check_unclosed(line) || check_meta_char(line))
			handle_syntax_error(&line, &dir);
		else
			history_nd_process(&line, &dir, &my_env, &status);
	}
	cleanup_resources(&dir, my_env);
	return (adjust_exit_status(dir.exit_status_));
}
