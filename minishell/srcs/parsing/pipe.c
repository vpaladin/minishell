/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:15:32 by vpaladin          #+#    #+#             */
/*   Updated: 2021/08/25 16:37:27 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_pipe(void)
{
	ft_putendl_fd("minishell: syntax error near unexpected token '|'", 2);
	ft_if_head_NULL();
	g_shell.exit_code = 258;
}

int	open_pipe(char **line, char **tmp, t_arg **head)
{
	(*line)++;
	if (**line == '|')
	{
		g_shell.destroy = 1;
		return (0);
	}
	if (ft_strcmp(*tmp, "") != 0)
		ft_add_arg(head, ft_new_arg(*tmp, g_shell.s_quotes));
	else
		free(*tmp);
	if (*head == NULL)
	{
		error_pipe();
		return (2);
	}
	g_shell.flag_pip_next = 1;
	if (execute(head, tmp) == 2)
		return (2);
	while (**line == ' ')
		(*line)++;
	if (**line == 0)
		error_pipe();
	return (0);
}
