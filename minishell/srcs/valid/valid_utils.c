/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lverkart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 14:04:04 by lverkart          #+#    #+#             */
/*   Updated: 2021/08/25 14:04:15 by lverkart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_export_all(char *arg)
{
	int	i;

	if (!ft_isalpha(arg[0]))
		return (0);
	i = -1;
	while (arg[++i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]))
		{
			if (arg[i] == '+' && arg[i + 1] == '=')
				return (i + 1);
			return (0);
		}
	}
	return (1);
}

int	is_inv_export(t_arg *arg, t_meg *shell)
{
	char	*n;

	if (!valid_export_all(arg->arg))
		return (0);
	n = ft_strchr(arg->arg, '=');
	if (n && n != arg->arg && n[1] != '\0')
	{
		shell->inviz_export++;
		return (1);
	}
	return (0);
}

void	ft_add_front(t_arg **head, t_arg *arg, t_meg *shell)
{
	arg->next = *head;
	*head = arg;
	shell->flag_export = 0;
}
