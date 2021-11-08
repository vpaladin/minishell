/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:14:39 by vpaladin          #+#    #+#             */
/*   Updated: 2021/08/25 14:14:12 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstnew_env_two(t_env	*ret, char	*n)
{
	ret->equal = 1;
	n[0] = '\0';
	ret->name = ft_strdup(ret->line);
	if (n[1] == '\0')
		ret->value = ft_strdup("");
	else
		ret->value = ft_strdup(&n[1]);
	n[0] = '=';
}

t_env	*ft_lstnew_env(char *env, int print)
{
	t_env	*ret;
	char	*n;

	ret = malloc(sizeof(t_env));
	if (!ret)
		ft_error(NULL, 1, 12);
	ret->line = ft_strdup(env);
	n = ft_strchr(ret->line, '=');
	if (n)
		ft_lstnew_env_two(ret, n);
	else
	{
		ret->name = ft_strdup(env);
		ret->value = NULL;
		ret->equal = 0;
	}
	ret->alpha = 0;
	ret->print = print;
	if (!ft_strncmp(ret->line, "_=", 2))
		ret->print = 0;
	ret->next = NULL;
	return (ret);
}

int	ft_lstadd_env(t_env **lst, t_env *new)
{
	t_env	*buf;

	if (!new || !lst)
		return (1);
	if (!*lst)
		*lst = new;
	else
	{
		buf = *lst;
		while (buf->next != NULL)
		{
			buf = buf->next;
		}
		buf->next = new;
	}
	return (0);
}

t_env	*ft_null_env(void)
{
	t_env	*shenv;
	char	*tmp;
	char	*buf;

	tmp = getcwd(NULL, 0);
	buf = tmp;
	tmp = ft_strjoin("PWD=", tmp);
	free(buf);
	shenv = ft_lstnew_env(tmp, 1);
	free(tmp);
	tmp = ft_strdup("SHLVL=1");
	ft_lstadd_env(&shenv, ft_lstnew_env(tmp, 1));
	free(tmp);
	return (shenv);
}

t_env	*create_env(char **env)
{
	int		i;
	t_env	*shenv;
	int		shlvl;
	char	*tmp;

	if (*env == NULL)
		return (ft_null_env());
	shenv = ft_lstnew_env(env[0], 1);
	i = 0;
	while (env[++i] != NULL)
	{	
		if (!ft_strncmp(env[i], "SHLVL=", 6))
		{
			shlvl = ft_atoi(env[i] + 6) + 1;
			tmp = ft_itoa(shlvl);
			env[i] = ft_strjoin("SHLVL=", tmp);
			free(tmp);
		}
		ft_lstadd_env(&shenv, ft_lstnew_env(env[i], 1));
	}
	return (shenv);
}
