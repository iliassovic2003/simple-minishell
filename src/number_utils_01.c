/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_utils_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:47:05 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/21 16:54:15 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_all_num(char *str)
{
	if (!*str)
		return (0);
	while (*str)
	{
		if ((*str >= 'A' && *str <= 'Z') || (*str >= 'a' && *str <= 'z')
			|| *str == '_')
			return (0);
		str++;
	}
	return (1);
}

static int	helper_quotes(const char *str, int *i, int *quote_type)
{
	if (*quote_type == 0)
	{
		if (str[*i] == '\"')
			*quote_type = 1;
		else
			*quote_type = 2;
	}
	else if ((*quote_type == 1 && str[*i] == '\'') || (*quote_type == 2
			&& str[*i] == '\"'))
	{
		printf("✘ mish: exit: %s: numeric argument required\n", str);
		return (2);
	}
	(*i)++;
	return (0);
}

static unsigned long long	ft_helper(const char *str, int *i,
		unsigned long long *number, int *quote_type)
{
	int	ret;

	while (str[*i])
	{
		if (str[*i] >= '0' && str[*i] <= '9')
		{
			*number = (*number * 10) + (str[(*i)++] - '0');
			if (*number >= LONG_MAX)
				return (-1);
		}
		else if (str[*i] == '\"' || str[*i] == '\'')
		{
			ret = helper_quotes(str, i, quote_type);
			if (ret != 0)
				return (ret);
		}
		else
			break ;
	}
	return (*number);
}

unsigned long long	ft_atoi(const char *str)
{
	unsigned long long	number;
	int					sign;
	int					i;
	int					quote_flag;

	sign = 1;
	number = 0;
	i = 0;
	quote_flag = 0;
	if (!str)
		return (0);
	i = ft_skip_whitespace(str, &i, &quote_flag);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && (str[i] == '\"' || str[i] == '\''))
		if (ft_handle_quotes(str[i++], &quote_flag))
			continue ;
	number = ft_helper(str, &i, &number, &quote_flag);
	if ((int)number == -1 || (int)number == 0)
		return (number);
	return (sign * number);
}
