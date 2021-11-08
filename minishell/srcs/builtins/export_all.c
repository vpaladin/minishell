/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 15:53:22 by lverkart          #+#    #+#             */
/*   Updated: 2021/08/25 21:22:06 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_without_plus(char **arg, int pos)
{
	char	*tmp;

	tmp = *arg;
	tmp[pos] = '\0';
	*arg = ft_strjoin(tmp, &tmp[pos + 1]);
	free(tmp);
}

void	export_plus(t_env **env, t_env *tmp)
{
	char	*buf;

	if (!(*env)->equal)
	{
		buf = (*env)->line;
		(*env)->line = ft_strjoin((*env)->line, "=");
		free(buf);
	}
	buf = (*env)->line;
	(*env)->line = ft_strjoin((*env)->line, tmp->value);
	free(buf);
	free(tmp->line);
	buf = (*env)->value;
	(*env)->value = ft_strjoin((*env)->value, tmp->value);
	free(buf);
	free(tmp->value);
	(*env)->print = tmp->print;
	(*env)->equal = tmp->equal;
}

void	ft_export_all_general(t_env	**env, t_env **tmp, int	*flag, int plus)
{
	if (!ft_strcmp((*env)->name, (*tmp)->name))
	{
		*flag = 1;
		if ((*tmp)->equal && plus > 1)
			export_plus(env, *tmp);
		else if ((*tmp)->equal)
		{
			free((*env)->line);
			free((*env)->value);
			(*env)->line = (*tmp)->line;
			(*env)->value = (*tmp)->value;
			(*env)->print = (*tmp)->print;
			(*env)->equal = (*tmp)->equal;
		}
		else
			free((*tmp)->line);
		free((*tmp)->name);
		free(*tmp);
	}
	*env = (*env)->next;
}

void	ft_export_err_valid(char *arg)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": not a valid identifier", 2);
	g_shell.exit_code = 1;
	return ;
}

void	ft_export_all(t_meg *shell, char **arg)
{
	int		flag;
	int		i;
	t_env	*tmp;
	t_env	*env;
	int		plus;

	i = 0;
	while (arg[++i] != NULL)
	{
		plus = valid_export_all(arg[i]);
		if (!plus)
			return (ft_export_err_valid(arg[i]));
		if (plus > 1)
			export_without_plus(&arg[i], plus - 1);
		tmp = ft_lstnew_env(arg[i], shell->flag_export);
		env = shell->t_env;
		flag = 0;
		while (flag == 0 && env != NULL)
			ft_export_all_general(&env, &tmp, &flag, plus);
		if (flag == 0)
			ft_lstadd_env(&shell->t_env, tmp);
	}
	shell->exit_code = 0;
}
