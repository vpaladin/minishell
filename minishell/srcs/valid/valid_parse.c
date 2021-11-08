/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:15:57 by vpaladin          #+#    #+#             */
/*   Updated: 2021/08/25 15:52:36 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valide_parse_first_step(t_meg *shell, t_arg **head)
{
	t_arg	*arg;
	int		dir;

	shell->inviz_export = 0;
	shell->flag_export = 1;
	g_shell.will_not_build = 0;
	arg = *head;
	while (arg != NULL)
	{
		dir = is_redirect(head, &arg, shell);
		if (dir > 1)
		{
			if (dir == 258)
				return (1);
			else if (dir >= 2)
				g_shell.exit_code = 1;
			else
				g_shell.exit_code = 2;
			return (dir);
		}
		if (!dir)
			arg = arg->next;
	}
	return (0);
}

int	valide_parse_second_step(char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_shell.exit_code = 127;
	g_shell.will_not_build = 1;
	ft_if_head_NULL();
	return (127);
}

void	valid_parse_step_more(t_meg *shell, int *i, char *arg)
{
	int		n;

	n = -1;
	while (*i != 1 && shell->build[++n] != NULL)
		if (!ft_strcmp(shell->build[n], arg))
			*i = 1;
	if (*i != 1 && !ft_valid_cmd(shell, arg, -1, 1))
		*i = 2;
}

int	valid_parse(t_meg *shell, t_arg **head, t_arg *arg, int i)
{
	i = valide_parse_first_step(shell, head);
	if (i)
		return (i);
	arg = *head;
	while (arg != NULL)
	{
		if (!i)
		{
			valid_parse_step_more(shell, &i, arg->arg);
			if ((i != 1 && i != 2) && !is_inv_export(arg, shell))
				return (valide_parse_second_step(arg->arg));
			if (i == 1 || i == 2)
			{
				while (shell->inviz_export)
				{
					shell->inviz_export--;
					del_redirect(head, head, 0);
				}
			}
		}
		arg = arg->next;
	}
	if (shell->inviz_export)
		ft_add_front(head, ft_new_arg(ft_strdup("export"), 0), shell);
	return (0);
}
