/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lverkart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 15:58:17 by lverkart          #+#    #+#             */
/*   Updated: 2021/08/24 15:58:19 by lverkart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_chdir(t_meg *shell, char *dir, char	**arg)
{
	if (chdir(dir) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->argument[1], 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		g_shell.exit_code = 1;
	}
	else
	{
		arg[1] = ft_strjoin("OLDPWD=", shell->pwd);
		ft_export_all(shell, arg);
		free(arg[1]);
		arg[1] = NULL;
		shell->exit_code = 0;
	}
}

char	**ft_cd_work(t_meg *shell)
{
	int		i;
	t_env	*buf;
	char	**arg;

	i = 0;
	arg = malloc(sizeof(char *) * 3);
	if (!arg)
		ft_error(NULL, 1, 12);
	arg[2] = NULL;
	buf = shell->t_env;
	if (shell->argument[1] != NULL)
		ft_chdir(shell, shell->argument[1], arg);
	else
	{
		while (buf != NULL && i == 0)
		{
			if (!ft_strcmp("HOME", buf->name))
				i = 1;
			if (i == 0)
				buf = buf->next;
		}
		if (i == 1)
			ft_chdir(shell, buf->value, arg);
	}
	return (arg);
}

void	ft_cd(t_meg *shell)
{
	char	**arg;
	char	*tmp;

	arg = ft_cd_work(shell);
	if (shell->exit_code == 0)
	{
		tmp = getcwd(NULL, 0);
		if (!tmp)
		{
			ft_putstr_fd(ERROR_DEL_CD, 2);
			g_shell.exit_code = 0;
			free(arg);
			return ;
		}
		free(shell->pwd);
		shell->pwd = tmp;
		arg[1] = ft_strjoin("PWD=", shell->pwd);
		ft_export_all(shell, arg);
		free(arg[1]);
		arg[1] = NULL;
	}
	arg[0] = NULL;
	free(arg);
	arg = NULL;
}
