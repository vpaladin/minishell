/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:15:39 by vpaladin          #+#    #+#             */
/*   Updated: 2021/08/24 15:06:27 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*one_dollar(char *str, char **line, char *tmp)
{
	char	*res;

	res = ft_str_addchar(tmp, '$');
	*line = str;
	return (res);
}

static char	*variable(char **str)
{
	int		i;
	char	*var;
	char	*tmp;

	tmp = *str;
	i = 0;
	var = ft_strdup("");
	var = ft_str_addchar(var, tmp[i]);
	if (tmp[i] == '?' || (tmp[i] >= '1' && tmp[i] <= '9'))
		i++;
	else
	{
		i++;
		while (ft_isalnum(tmp[i]) == 1 && tmp[i] != ' ')
		{
			var = ft_str_addchar(var, tmp[i]);
			i++;
		}
	}
	*str = tmp + i;
	return (var);
}

static char	*find_env_var(char *tmp, char *var, t_env *head, char *res)
{
	char	*temp;

	if (ft_strcmp(var, "?") == 0)
	{
		temp = ft_itoa(g_shell.exit_code);
		res = ft_strjoin(tmp, temp);
		free(tmp);
		free(temp);
	}
	else
	{
		while (head != NULL)
		{
			if (ft_strcmp(var, head->name) == 0)
			{
				res = ft_strjoin(tmp, head->value);
				free(tmp);
				break ;
			}
			head = head->next;
		}
	}
	return (res);
}

char	*env_var(t_meg *shell, char **line, char *tmp)
{
	char	*str;
	char	*var;
	char	*res;
	t_env	*head;

	str = ++(*line);
	if (ft_isalnum(*str) == 0 && *str != '?')
		return (one_dollar(str, line, tmp));
	res = NULL;
	var = variable(&str);
	head = shell->t_env;
	res = find_env_var(tmp, var, head, res);
	if (var)
		free(var);
	if (!res && g_shell.quotes != 1 && ft_strcmp(tmp, "") == 0)
		g_shell.flag_dollar = 1;
	if (!res)
		res = tmp;
	*line = str;
	return (res);
}
