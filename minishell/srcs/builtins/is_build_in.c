/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_build_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:15:22 by vpaladin          #+#    #+#             */
/*   Updated: 2021/08/20 12:53:29 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_exe(t_meg *shell, int *fd)
{
	if (shell->flag_pip_last)
	{
		close(shell->pipe);
		shell->flag_pip_last = 0;
	}
	if (shell->flag_pip_next)
	{
		shell->flag_pip_last = 1;
		shell->flag_pip_next = 0;
		shell->pipe = fd[0];
		close(fd[1]);
	}
	if (shell->flag_op_fd)
	{
		shell->flag_op_fd = 0;
		close(shell->rpipe);
	}
	return (0);
}

int	error_fork_exe(t_meg *shell, int *fd)
{
	close(fd[0]);
	close(fd[1]);
	ft_putendl_fd("minishell: fork: Resource temporarily unavailable", 2);
	shell->exit_code = 1;
	shell->flag_pip_last = 0;
	shell->flag_pip_next = 0;
	ft_if_head_NULL();
	return (128);
}

int	ft_exe(t_meg *shell, int flag, int build)
{
	int	fd[2];
	int	id;

	if (shell->flag_pip_next)
	{
		if (pipe(fd) == -1)
		{
			ft_error(NULL, 0, 32);
			return (32);
		}
	}
	if (flag)
	{
		shell->flag_code_wait = 1;
		shell->count_wait++;
		id = fork();
		defoult_singnal();
		if (id < 0)
			return (error_fork_exe(shell, fd));
		if (id == 0)
			ft_pipex(shell, fd);
	}
	else if (!flag)
		build_in(shell, build, fd);
	return (close_exe(shell, fd));
}

int	is_build_in(t_meg *shell)
{
	int	i;
	int	flag;

	errno = 0;
	flag = 1;
	i = -1;
	if (g_shell.will_not_build == 1)
		return (0);
	while (flag && shell->build[++i] != NULL)
		if (ft_strcmp(shell->build[i], shell->argument[0]) == 0)
			flag = 0;
	return (ft_exe(shell, flag, i));
}
