/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lverkart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 15:50:15 by lverkart          #+#    #+#             */
/*   Updated: 2021/08/24 15:50:17 by lverkart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_whithout_n(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 0;
	while (arg[++i])
	{
		if (arg[i] != 'n')
			return (0);
	}
	return (1);
}

void	ft_echo(t_meg *shell, int i, int n)
{
	int	non;

	if (shell->argument[1] == NULL)
	{
		ft_putstr_fd("\n", 1);
		shell->exit_code = 0;
		return ;
	}
	while (shell->argument[i] != NULL && n)
	{
		n = ft_whithout_n(shell->argument[i]);
		if (n)
			i++;
	}
	non = i;
	while (shell->argument[i] != NULL)
	{
		ft_putstr_fd(shell->argument[i], 1);
		if (shell->argument[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (non == 1)
		ft_putstr_fd("\n", 1);
	shell->exit_code = 0;
}
