/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:45:59 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/20 22:41:26 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	nested_quotes(char *str)
{
	int	i;
	int	double_quotes;
	int	single_quotes;

	i = 0;
	double_quotes = 0;
	single_quotes = 0;
	if (!*str)
		return (0);
	while (str[i])
	{
		if (str[i] == '"')
			double_quotes = 1;
		else if (str[i] == '\'')
			single_quotes = 1;
		i++;
	}
	if (double_quotes && single_quotes)
		return (2);
	return (0);
}

void	handle_quotes(const char *t, size_t *i, int q[3])
{
	if (t[*i] == '"' && !q[1])
	{
		if (!q[2])
			q[2] = 2;
		q[0] = !q[0];
		(*i)++;
	}
	else if (t[*i] == '\'' && !q[0])
	{
		if (!q[2])
			q[2] = 1;
		q[1] = !q[1];
		(*i)++;
	}
}

int	ft_handle_quotes(const char c, int *quote_flag)
{
	if (c == '\"' && !(*quote_flag))
	{
		*quote_flag = 1;
		return (1);
	}
	else if (c == '\'' && !(*quote_flag))
	{
		*quote_flag = 2;
		return (1);
	}
	return (0);
}

int	ft_skip_whitespace(const char *str, int *i, int *quote_flag)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'
			|| str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'
			|| str[*i] == '\"' || str[*i] == '\''))
	{
		if (ft_handle_quotes(str[*i], quote_flag))
			(*i)++;
		else
			(*i)++;
	}
	return (*i);
}
