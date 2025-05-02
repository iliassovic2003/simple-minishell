/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:43:14 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/20 21:28:24 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	directory_fill(t_dir *dir, t_env *tmp)
{
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, "PWD"))
		{
			if (dir->dir)
				free(dir->dir);
			dir->dir = ft_strdup(tmp->value);
		}
		if (!ft_strcmp(tmp->var, "OLDPWD"))
		{
			if (dir->oldir)
				free(dir->oldir);
			dir->oldir = ft_strdup(tmp->value);
		}
		if (!ft_strcmp(tmp->var, "HOME"))
		{
			if (dir->home)
				free(dir->home);
			dir->home = ft_strdup(tmp->value);
		}
		tmp = tmp->next;
	}
}

void	update_directory(t_dir *dir, t_env *my_env)
{
	t_env	*tmp;
	char	buf[PATH_MAX];

	if (!my_env)
	{
		printf("✘ mish: env: Environement Not Found ...\n");
		dir->exit_status_ = 1;
	}
	else
	{
		tmp = my_env;
		if (!getcwd(buf, sizeof(buf)))
		{
			perror("✘ getcwd");
			return ;
		}
		directory_fill(dir, tmp);
		if (!dir->dir)
			dir->dir = ft_strdup(buf);
		if (!dir->oldir)
			dir->oldir = ft_strdup(buf);
	}
}

void	update_env_vars(t_env *tmp, char *buf, char **smp)
{
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, "PWD"))
		{
			*smp = ft_strdup(tmp->value);
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(buf);
		}
		if (!ft_strcmp(tmp->var, "OLDPWD"))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(*smp);
			break ;
		}
		tmp = tmp->next;
	}
}

void	handle_cd_no_arg(t_env *my_env, t_dir *dir)
{
	char	buf[PATH_MAX];
	char	*smp;
	t_env	*tmp;

	tmp = my_env;
	smp = NULL;
	if (chdir(dir->home) == -1)
	{
		if ((access(dir->home, W_OK | R_OK) == -1) || (access(dir->home,
					X_OK) == -1))
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

void	handle_cd_oldpwd(t_env *my_env, t_dir *dir)
{
	char	buf[PATH_MAX];
	char	*smp;
	t_env	*tmp;

	tmp = my_env;
	smp = NULL;
	if (chdir(dir->oldir) == -1)
	{
		if ((access(dir->oldir, W_OK | R_OK) == -1) || (access(dir->oldir,
					X_OK) == -1))
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
	printf("%s\n", buf);
}
