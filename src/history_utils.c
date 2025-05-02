/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:21:50 by eelkabia          #+#    #+#             */
/*   Updated: 2025/05/01 19:47:43 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int handle_heredoc(char *line, t_dir *dir, t_env *my_env)
{
	// khdem b line 3adi, dir->exit_status_ ghtdirha bach tmodifiha, o dik my_env ghnkhdm biha ana expand
}

void	history_nd_process(char **line, t_dir *dir, t_env **my_env,
		t_stat *status)
{
	add_history(*line);
	// if (<<) dir heredoc hna
	tilda_remod(line, *dir);
	process_input(line, dir, my_env, status);
}

char	*trim_whitespace(char *str)
{
	char	*end;

	while (isspace((unsigned char)*str))
		str++;
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end))
		end--;
	*(end + 1) = '\0';
	return (str);
}
