/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lverkart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:13:42 by lverkart          #+#    #+#             */
/*   Updated: 2021/08/24 16:13:44 by lverkart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pre_papix(t_meg *shell, int *fd)
{
	if (shell->flag_pip_next)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
	}
	if (shell->flag_op_fd)
	{
		dup2(shell->rpipe, 1);
		close(shell->rpipe);
	}
	if (shell->flag_pip_last)
	{
		dup2(shell->pipe, 0);
		close(shell->pipe);
	}
	else if (shell->if_null_lred == 1)
		exit(1);
}

void	ft_pipex(t_meg *shell, int *fd)
{
	char	*tmpcmd;
	int		i;
	char	*buf;

	buf = ft_strdup(shell->argument[0]);
	ft_pre_papix(shell, fd);
	execve(shell->argument[0], shell->argument, shell->new_env);
	tmpcmd = ft_strjoin("/", shell->argument[0]);
	i = -1;
	while (shell->path[++i] != NULL)
	{
		free(shell->argument[0]);
		shell->argument[0] = ft_strjoin(shell->path[i], tmpcmd);
		execve(shell->argument[0], shell->argument, shell->new_env);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(buf, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	exit(126);
}
