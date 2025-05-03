/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:10:39 by eelkabia          #+#    #+#             */
/*   Updated: 2025/05/03 13:10:30 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**parse_prompt_to_argv(const char *input)
{
	int		argc;
	char	**argv;
	int		i;

	i = 0;
	if (!input)
		return (NULL);
	argc = count_args(input);
	if (argc == 0)
		return (NULL);
	argv = malloc((argc + 1) * sizeof(char *));
	if (!argv)
		return (NULL);
	while (i < argc)
	{
		argv[i] = get_next_arg(&input);
		if (!argv[i])
		{
			free_argv(argv, i);
			return (NULL);
		}
		i++;
	}
	argv[argc] = NULL;
	return (argv);
}

int	quotes_error(char *str)
{
	printf("✘ FATAL ERROR: Unclosed %s Quotes ... Try Again\n", str);
	return (1);
}

int	check_unclosed(char *line)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		if (line[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	if (in_single_quote)
		return (quotes_error("Single"));
	if (in_double_quote)
		return (quotes_error("Double"));
	return (0);
}

char	*special_check(const char *token, t_env *env, int last_exit_status)
{
	t_tmp	tmp;
	int		quote[3];

	tmp.result = malloc(PATH_MAX);
	if (!tmp.result)
		return (NULL);
	tmp.i = 0;
	tmp.j = 0;
	quote[0] = 0;
	quote[1] = 0;
	quote[2] = 0;
	while (token[tmp.i])
	{
		handle_quotes(token, &tmp.i, quote);
		if (token[tmp.i] == '$' && !quote[1])
			handle_dollar(token, &tmp, env, last_exit_status);
		else if ((quote[2] == 2 && token[tmp.i] == '"') || (quote[2] == 1
				&& token[tmp.i] == '\''))
			(tmp.i)++;
		else if (token[tmp.i])
			tmp.result[(tmp.j)++] = token[(tmp.i)++];
	}
	tmp.result[tmp.j] = '\0';
	return (tmp.result);
}

void	tilda_remod(char **line, t_dir dir)
{
	char	**tokens;
	char	*new_line;

	if (!*line || !dir.home)
		return ;
	tokens = ft_split(*line, ' ');
	if (!tokens)
		return ;
	new_line = build_new_line(tokens, dir);
	free_array(tokens);
	if (!new_line)
		return ;
	free(*line);
	*line = new_line;
}
