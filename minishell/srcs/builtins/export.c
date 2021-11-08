/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lverkart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:00:57 by lverkart          #+#    #+#             */
/*   Updated: 2021/08/24 16:00:59 by lverkart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_declare_export(t_meg *shell, int i)
{
	t_env	*env;
	t_env	*buf;

	while (i >= 0)
	{
		env = shell->t_env;
		buf = NULL;
		while (env != NULL && buf == NULL)
		{
			if (env->alpha == 0)
				buf = env;
			env = env->next;
		}
		if (buf == NULL)
			return (i);
		env = shell->t_env;
		while (env != NULL)
		{
			if (env->alpha == 0 && ft_strcmp(buf->name, env->name) > 0)
				buf = env;
			env = env->next;
		}
		buf->alpha = ++i;
	}
	return (i);
}

void	ft_print_export(t_meg *shell, int sum)
{
	t_env	*env;
	int		i;

	i = 0;
	while (++i <= sum)
	{
		env = shell->t_env;
		while (env != NULL)
		{
			if (env->alpha == i)
			{
				env->alpha = 0;
				if (env->print)
				{
					printf("declare -x %s", env->name);
					if (env->value)
						printf("=\"%s\"", env->value);
					printf("\n");
				}
			}
			env = env->next;
		}
	}
}

void	ft_export(t_meg *shell)
{
	if (shell->argument[1] == NULL)
		ft_print_export(shell, ft_declare_export(shell, 0));
	ft_export_all(shell, shell->argument);
}
