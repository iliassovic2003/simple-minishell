/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:43:59 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/21 16:54:02 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_cd_path(char **split, t_env *my_env, t_dir *dir)
{
	char	buf[PATH_MAX];
	char	*smp;
	t_env	*tmp;

	tmp = my_env;
	smp = NULL;
	if (chdir(split[1]) == -1)
	{
		if ((access(split[1], W_OK | R_OK) == -1)
			|| (access(split[1], X_OK) == -1))
		{
			perror("✘ cd");
			dir->exit_status_ = 1;
		}
		return ;
	}
	if (!getcwd(buf, sizeof(buf)))
	{
		perror("✘ getcwd");
		return ;
	}
	update_env_vars(tmp, buf, &smp);
}
