/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils_01.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:19:16 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/30 21:15:41 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_redirection(char *operator, char *filename)
{
	int	fd;

	fd = 0;
	if (!ft_strcmp(operator, ">"))
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (!ft_strcmp(operator, ">>"))
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (!ft_strcmp(operator, "<"))
		fd = open(filename, O_RDONLY);
	if (fd < 0)
		perror("open");
	else
	{
		if (!ft_strcmp(operator, ">") || !ft_strcmp(operator, ">>"))
			dup2(fd, STDOUT_FILENO);
		else
			dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

// static void	handle_heredoc_child(char *delimiter, int *fd_pipe)
// {
// 	char	*line;

// 	close(fd_pipe[0]);
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line || !ft_strcmp(line, delimiter))
// 			break ;
// 		write(fd_pipe[1], line, ft_strlen(line));
// 		write(fd_pipe[1], "\n", 1);
// 		free(line);
// 	}
// 	if (!line)
// 		write(STDERR_FILENO, "\n", 1);
// 	free(line);
// 	close(fd_pipe[1]);
// 	exit(0);
// }

// static int	handle_heredoc(char *delimiter, char **tokens)
// {
// 	int		fd_pipe[2];
// 	pid_t	pid;
// 	int		status;

// 	if (pipe(fd_pipe) < 0)
// 		return (perror("pipe"), 1);
// 	pid = fork();
// 	if (pid == 0)
// 		handle_heredoc_child(delimiter, fd_pipe);
// 	else if (pid > 0)
// 	{
// 		close(fd_pipe[1]);
// 		waitpid(pid, &status, 0);
// 		if (WIFSIGNALED(status) && handle_signals(status, fd_pipe[0], tokens))
// 			return (1);
// 		dup2(fd_pipe[0], STDIN_FILENO);
// 		close(fd_pipe[0]);
// 	}
// 	else
// 		return (perror("fork"), 1);
// 	return (0);
// }

void	check_redirections(char *str)
{
	char	**tokens;
	int		i;

	tokens = ft_split(str, ' ');
	if (!tokens)
		return ;
	i = -1;
	while (tokens[++i])
	{
		if (!ft_strcmp(tokens[i], "<<") && tokens[i + 1])
		{
			if (handle_heredoc(tokens[i + 1], tokens))
				return ;
			i++;
		}
		else if ((!ft_strcmp(tokens[i], ">") || !ft_strcmp(tokens[i], ">>")
				|| !ft_strcmp(tokens[i], "<")) && tokens[i + 1])
		{
			handle_redirection(tokens[i], tokens[i + 1]);
			i++;
		}
	}
	free_array(tokens);
}
