/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 13:55:04 by lverkart          #+#    #+#             */
/*   Updated: 2021/08/26 13:19:58 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	writing_heredoc_two(char **line, char **arg, char	**heredoc)
{
	char	*tmp;

	while (ft_strcmp(*line, *arg))
	{
		*line = ft_str_addchar(*line, '\n');
		tmp = *heredoc;
		*heredoc = ft_strjoin(*heredoc, *line);
		free(tmp);
		free(*line);
		*line = readline("> ");
		if (*line == NULL)
		{
			*line = ft_strdup("");
			break ;
		}
	}
}

void	writing_heredoc(int *fd, char *arg)
{
	char	*heredoc;
	char	*line;

	sig_in_redirect();
	heredoc = ft_strdup("");
	close(fd[0]);
	line = readline("> ");
	if (line == NULL)
	{
		free(heredoc);
		close(fd[1]);
		exit(2);
	}
	writing_heredoc_two(&line, &arg, &heredoc);
	free(line);
	write(fd[1], heredoc, ft_strlen(heredoc));
	free(heredoc);
	close(fd[1]);
	exit(1);
}

int	redir_fork_error(t_meg *shell, int *fd)
{
	mod_singnal();
	close(fd[0]);
	close(fd[1]);
	ft_putendl_fd("minishell: fork: Resource temporarily unavailable", 2);
	shell->exit_code = 1;
	shell->flag_pip_last = 0;
	return (128);
}

int	ll_redirect(char *arg, t_meg *shell, int qoutes)
{
	int		fd[2];
	int		id;
	int		status;

	if ((!ft_strncmp("<", arg, 1) || !ft_strncmp(">", arg, 1)) && !qoutes)
		return (redir_syntax_err(arg));
	if (pipe(fd) == -1)
	{
		ft_error(NULL, 0, 32);
		return (32);
	}
	if (shell->flag_pip_last == 1)
		close(shell->pipe);
	shell->flag_pip_last = 1;
	shell->pipe = fd[0];
	id = fork();
	defoult_singnal();
	if (id < 0)
		return (redir_fork_error(shell, fd));
	if (id == 0)
		writing_heredoc(fd, arg);
	waitpid(id, &status, 0);
	close(fd[1]);
	mod_singnal();
	return (WEXITSTATUS(status));
}
