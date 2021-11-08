/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lverkart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 13:45:35 by lverkart          #+#    #+#             */
/*   Updated: 2021/08/25 13:45:36 by lverkart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_syntax_err(char *arg)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("'\n", 2);
	g_shell.exit_code = 258;
	return (258);
}

int	r_redirect(char *arg, t_meg *shell, int qoutes)
{
	if ((!ft_strncmp("<", arg, 1) || !ft_strncmp(">", arg, 1)) && !qoutes)
		return (redir_syntax_err(arg));
	if (shell->flag_op_fd == 1)
		close(shell->rpipe);
	shell->flag_op_fd = 1;
	shell->rpipe = open(arg, O_CREAT | O_TRUNC | O_RDWR, 0644);
	return (1);
}

int	rr_redirect(char *arg, t_meg *shell, int qoutes)
{
	if ((!ft_strncmp("<", arg, 1) || !ft_strncmp(">", arg, 1)) && !qoutes)
		return (redir_syntax_err(arg));
	if (shell->flag_op_fd == 1)
		close(shell->rpipe);
	shell->flag_op_fd = 1;
	shell->rpipe = open(arg, O_CREAT | O_APPEND | O_RDWR, 0644);
	return (1);
}

int	l_redirect(char *arg, t_meg *shell, int qoutes)
{
	if ((!ft_strncmp("<", arg, 1) || !ft_strncmp(">", arg, 1)) && !qoutes)
		return (redir_syntax_err(arg));
	if (shell->flag_pip_last == 1)
		close(shell->pipe);
	shell->flag_pip_last = 1;
	shell->pipe = open(arg, O_RDWR, 0644);
	if (shell->pipe < 0)
	{
		if (shell->if_null_lred == 0)
		{
			if (shell->flag_pip_last)
			{
				dup2(shell->pipe, 0);
				close(shell->pipe);
				shell->flag_pip_last = 0;
			}
			shell->if_null_lred = 1;
		}
		ft_error(arg, 0, 2);
		return (2);
	}
	shell->if_null_lred = 2;
	return (1);
}
