/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:12:55 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/20 22:07:13 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_par(char **data, const char *msg)
{
	write(2, msg, ft_strlen(msg));
	if (data)
		free_array(data);
	exit(1);
}

void	ft_error(char *str, int n)
{
	ft_putstr_fd(str, 2);
	exit(n);
}

void	ft_perror(char *str, int n)
{
	perror(str);
	exit(n);
}

void	ft_cmd(char *str, char **cmd, int n)
{
	if (!cmd || !*cmd)
	{
		ft_putendl_fd(str, 2);
		exit(n);
	}
	ft_putstr_fd(str, 2);
	ft_putendl_fd(cmd[0], 2);
	exit(n);
}
