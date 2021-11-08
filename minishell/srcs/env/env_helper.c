/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:14:39 by vpaladin          #+#    #+#             */
/*   Updated: 2021/08/24 15:10:12 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inport_env_final(t_meg *shell)
{
	t_env	*env;
	int		i;

	env = shell->t_env;
	i = -1;
	while (env != NULL)
	{
		if (env->print)
		{
			shell->new_env[++i] = ft_strdup(env->line);
			if (!shell->new_env[i])
				ft_error(NULL, 1, 12);
		}
		env = env->next;
	}
}

void	inport_env(t_meg *shell)
{
	t_env	*env;
	int		i;

	i = -1;
	while (shell->new_env && shell->new_env[++i])
	{
		free (shell->new_env[i]);
		shell->new_env[i] = NULL;
	}
	free(shell->new_env);
	shell->new_env = NULL;
	i = 0;
	env = shell->t_env;
	while (env != NULL)
	{
		if (env->print)
			i++;
		env = env->next;
	}
	shell->new_env = malloc(sizeof(char *) * (i + 1));
	if (!shell->new_env)
		ft_error(NULL, 1, 12);
	shell->new_env[i] = NULL;
	inport_env_final(shell);
}

void	init_path(t_meg *shell)
{
	t_env	*shenv;
	int		i;

	inport_env(shell);
	i = -1;
	while (shell->path && shell->path[++i])
	{
		free (shell->path[i]);
		shell->path[i] = NULL;
	}
	free(shell->path);
	shell->path = NULL;
	shenv = shell->t_env;
	while (shenv != NULL)
	{
		if (!ft_strcmp("PATH", shenv->name))
			shell->path = ft_split(shenv->line, ':');
		shenv = shenv->next;
	}
}
