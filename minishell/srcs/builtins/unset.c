/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lverkart <lverkart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:15:22 by lverkart          #+#    #+#             */
/*   Updated: 2021/08/20 12:53:29 by lverkart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_head(t_meg *shell, t_env **shenv)
{
	shell->t_env = shell->t_env->next;
	free(*shenv);
	*shenv = NULL;
	shell->exit_code = 0;
	return ;
}

void	ft_unset(t_meg *shell, int i)
{
	t_env	*shenv;
	t_env	*tmp;

	shenv = shell->t_env;
	while (shenv != NULL && ++i)
	{
		if (!ft_strcmp(shell->argument[1], shenv->name))
		{
			free(shenv->name);
			free(shenv->value);
			free(shenv->line);
			if (i == 1)
				return (ft_unset_head(shell, &shenv));
			tmp->next = shenv->next;
			free(shenv);
			shenv = NULL;
		}
		else
		{
			tmp = shenv;
			shenv = shenv->next;
		}
	}
	shell->exit_code = 0;
}
