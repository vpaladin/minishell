/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 14:01:18 by lverkart          #+#    #+#             */
/*   Updated: 2021/08/25 15:34:05 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_arg_in_redir(t_arg	*buf)
{
	free(buf->next->arg);
	buf->next->arg = NULL;
	free(buf->next);
	buf->next = NULL;
	free(buf->arg);
	buf->arg = NULL;
	free(buf);
	buf = NULL;
}

void	del_redirect(t_arg **head, t_arg **arg, int flag)
{
	t_arg	*tmp;
	t_arg	*buf;

	tmp = *head;
	if (*head == *arg && ++flag)
		buf = tmp;
	else
	{
		while (tmp->next != *arg)
			tmp = tmp->next;
		buf = tmp->next;
	}
	if (flag)
		*head = tmp->next->next;
	else
		tmp->next = buf->next->next;
	del_arg_in_redir(buf);
	if (flag)
		*arg = *head;
	else
		*arg = tmp->next;
}

int	err_newline(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
	g_shell.exit_code = 258;
	return (258);
}

int	is_redirect_two(t_arg **head, t_arg **arg, t_meg *shell, int ret)
{
	if (!ft_strncmp(">>", (*arg)->arg, 2))
	{
		if ((*arg)->next == NULL)
			return (err_newline());
		ret = rr_redirect((*arg)->next->arg, shell, (*arg)->next->s_quotes);
		del_redirect(head, arg, 0);
		return (ret);
	}
	if (!ft_strncmp(">", (*arg)->arg, 1))
	{
		if ((*arg)->next == NULL)
			return (err_newline());
		ret = r_redirect((*arg)->next->arg, shell, (*arg)->next->s_quotes);
		del_redirect(head, arg, 0);
		return (ret);
	}
	return (0);
}

int	is_redirect(t_arg **head, t_arg **arg, t_meg *shell)
{
	int	ret;

	ret = 1;
	if ((*arg)->s_quotes)
		return (0);
	if (!ft_strncmp("<<", (*arg)->arg, 2))
	{
		if ((*arg)->next == NULL)
			return (err_newline());
		ret = ll_redirect((*arg)->next->arg, shell, (*arg)->next->s_quotes);
		del_redirect(head, arg, 0);
		return (ret);
	}
	if (!ft_strncmp("<", (*arg)->arg, 1))
	{
		if ((*arg)->next == NULL)
			return (err_newline());
		ret = l_redirect((*arg)->next->arg, shell, (*arg)->next->s_quotes);
		del_redirect(head, arg, 0);
		return (ret);
	}
	return (is_redirect_two(head, arg, shell, ret));
}
