/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pwd_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lverkart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:16:11 by lverkart          #+#    #+#             */
/*   Updated: 2021/08/24 16:16:14 by lverkart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_meg *shell)
{
	t_env	*shenv;

	shenv = shell->t_env;
	while (shenv != NULL)
	{
		if (shenv->equal && shenv->print)
			ft_putendl_fd(shenv->line, 1);
		shenv = shenv->next;
	}
	shell->exit_code = 0;
}

void	start_buil_in(t_meg *shell, int i)
{
	if (i == 0)
		ft_echo(shell, 1, 1);
	else if (i == 1)
		ft_exit(shell);
	else if (i == 2)
		ft_export(shell);
	else if (i == 3)
	{
		printf("%s\n", shell->pwd);
		shell->exit_code = 0;
	}
	else if (i == 4)
		ft_cd(shell);
	else if (i == 5)
		ft_env(shell);
	else if (i == 6)
		ft_unset(shell, 0);
}

void	build_in(t_meg *shell, int i, int *fd)
{
	if (i > 6)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->argument[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		shell->exit_code = 127;
		return ;
	}
	if (shell->flag_pip_next)
		dup2(fd[1], 1);
	if (shell->flag_op_fd)
		dup2(shell->rpipe, 1);
	if (shell->flag_pip_last)
		dup2(shell->pipe, 0);
	start_buil_in(shell, i);
	dup2(shell->original_fd0, 0);
	dup2(shell->original_fd1, 1);
	dup2(shell->original_fd2, 2);
}
