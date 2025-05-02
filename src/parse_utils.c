/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:44:41 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/20 18:17:01 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_args_util(char *input, int *in_quotes, char *quote_char)
{
	if ((*input == '\'' || *input == '"') && !(*in_quotes))
	{
		*in_quotes = 1;
		*quote_char = *input;
	}
	else if (*input == *quote_char && *in_quotes)
	{
		*in_quotes = 0;
		*quote_char = 0;
	}
	return (*in_quotes);
}

int	count_args(const char *input)
{
	int		count;
	int		in_quotes;
	char	quote_char;

	count = 0;
	in_quotes = 0;
	quote_char = 0;
	while (*input)
	{
		while (*input == ' ')
			input++;
		if (!*input)
			break ;
		count++;
		while (*input && (in_quotes || *input != ' '))
			in_quotes = count_args_util((char *)input++, &in_quotes,
					&quote_char);
	}
	return (count);
}

int	adjust_exit_status(int status)
{
	status %= 256;
	if (status < 0)
		status = 256 + status;
	return (status);
}

static void	gna_util(const char **input, int *in_quotes, char *quote_char)
{
	if ((**input == '\'' || **input == '"') && !(*in_quotes))
	{
		*in_quotes = 1;
		*quote_char = **input;
	}
	else if (**input == *quote_char && *in_quotes)
		*in_quotes = 0;
	(*input)++;
}

char	*get_next_arg(const char **input)
{
	const char	*start;
	int			in_quotes;
	char		quote_char;
	char		*arg;
	int			len;

	start = *input;
	in_quotes = 0;
	quote_char = 0;
	while (**input == ' ')
		(*input)++;
	start = *input;
	while (**input && (in_quotes || **input != ' '))
		gna_util(input, &in_quotes, &quote_char);
	len = *input - start;
	arg = malloc(len + 1);
	if (!arg)
		return (NULL);
	ft_strncpy(arg, start, len);
	arg[len] = '\0';
	return (arg);
}
