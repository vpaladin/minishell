/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:15:39 by vpaladin          #+#    #+#             */
/*   Updated: 2021/08/25 19:10:02 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expectation(void)
{
	while (g_shell.count_wait > 0)
	{
		waitpid(0, NULL, 0);
		g_shell.count_wait--;
	}
}

int	error_in_pipe(t_arg **head, int i, char **tmp)
{
	if (i == 1)
	{
		expectation();
		free_arg(*head);
		*head = NULL;
		return (2);
	}
	else if (i > 1)
	{
		free_arg(*head);
		*tmp = NULL;
		*head = NULL;
		return (0);
	}
	else if (*head == NULL)
	{
		ft_if_head_NULL();
		*tmp = NULL;
		return (0);
	}
	return (100);
}

int	execute(t_arg **head, char **tmp)
{
	char	**arguments;
	int		i;

	g_shell.if_null_lred = 0;
	init_path(&g_shell);
	i = valid_parse(&g_shell, head, NULL, 0);
	i = error_in_pipe(head, i, tmp);
	if (i == 2)
		return (2);
	if (i == 0)
		return (0);
	arguments = create_massiv(*head);
	g_shell.argument = arguments;
	if (is_build_in(&g_shell) == 128)
		g_shell.destroy = 1;
	free_arg(*head);
	freedom(arguments);
	*head = NULL;
	*tmp = NULL;
	return (0);
}
