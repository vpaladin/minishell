/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_megashell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:14:56 by vpaladin          #+#    #+#             */
/*   Updated: 2021/08/24 15:10:45 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_name_build(int i)
{
	char	**build;

	build = malloc(sizeof(char *) * 10);
	build[9] = NULL;
	build[0] = ft_strdup("echo");
	build[1] = ft_strdup("exit");
	build[2] = ft_strdup("export");
	build[3] = ft_strdup("pwd");
	build[4] = ft_strdup("cd");
	build[5] = ft_strdup("env");
	build[6] = ft_strdup("unset");
	build[7] = ft_strdup("..");
	build[8] = ft_strdup(".");
	while (++i < 9)
	{
		if (build[i] == NULL)
		{
			i = -1;
			while (++i < 9)
				free (build[i]);
			return (NULL);
		}
	}
	return (build);
}

void	init_pwd(t_meg *shell)
{
	t_env	*shenv;

	shenv = shell->t_env;
	while (shenv != NULL)
	{
		if (!ft_strcmp("PWD", shenv->name))
			shell->pwd = ft_strdup(shenv->value);
		shenv = shenv->next;
	}
}

void	init_megashell(t_meg *shell, char **env)
{
	shell->t_env = create_env(env);
	shell->flag_dollar = 0;
	shell->exit_code = 0;
	shell->flag_pip_next = 0;
	shell->flag_pip_last = 0;
	init_pwd(shell);
	shell->path = NULL;
	shell->new_env = NULL;
	shell->build = init_name_build(-1);
	shell->original_fd0 = dup(0);
	shell->original_fd1 = dup(1);
	shell->original_fd2 = dup(2);
	shell->count_wait = 0;
	shell->quotes = 0;
	shell->flag_code_wait = 0;
	rl_outstream = stderr;
}
