/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:14:10 by vpaladin          #+#    #+#             */
/*   Updated: 2021/08/25 12:52:57 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *name, int ex, int code)
{
	g_shell.exit_code = code;
	if (name)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(" : ", 2);
		ft_putendl_fd(strerror(g_shell.exit_code), 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd(strerror(g_shell.exit_code), 2);
	}
	if (ex)
		exit(g_shell.exit_code);
}

void	free_arg(t_arg *head)
{
	t_arg	*temp;
	t_arg	*list;

	list = head;
	while (list)
	{
		temp = list->next;
		if (list->arg)
			free(list->arg);
		free(list);
		list = temp;
	}
	head = NULL;
}

void	freedom(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
	{
		free(arg[i]);
		i++;
	}
	free(arg);
	arg = NULL;
}

void	close_fd(void)
{
	g_shell.flag_op_fd = 0;
	close(g_shell.rpipe);
}

void	ft_if_head_NULL(void)
{
	int	fd[2];

	if (g_shell.flag_pip_next)
	{
		if (pipe(fd) == -1)
		{
			ft_error(NULL, 0, 32);
			return ;
		}
	}
	if (g_shell.flag_pip_last)
	{
		close(g_shell.pipe);
		g_shell.flag_pip_last = 0;
	}
	if (g_shell.flag_pip_next)
	{
		g_shell.flag_pip_last = 1;
		g_shell.flag_pip_next = 0;
		g_shell.pipe = fd[0];
		close(fd[1]);
	}
	if (g_shell.flag_op_fd)
		close_fd();
}
