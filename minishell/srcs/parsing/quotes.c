/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:15:39 by vpaladin          #+#    #+#             */
/*   Updated: 2021/08/25 19:04:09 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*double_q(char *str, t_meg *shell, char *tmp, int *i)
{
	char	*temp;

	str++;
	(*i)++;
	while (*str != 34 && *str != 0)
	{
		if (*str == '$')
		{
			temp = str;
			tmp = env_var(shell, &str, tmp);
			*i += str - temp;
		}
		else
		{
			tmp = ft_str_addchar(tmp, *str);
			str++;
			*i += 1;
		}
	}
	return (tmp);
}

static char	*single_q(char *str, char *tmp, int *i)
{
	*i = 1;
	str++;
	while (*str != 39 && *str != 0)
	{
		tmp = ft_str_addchar(tmp, *str);
		str++;
		(*i)++;
	}
	return (tmp);
}

static char	*error_q(char **tmp, t_arg **head)
{
	free(*tmp);
	write(2, "minishell: unclosed quotes\n", 27);
	g_shell.exit_code = 1;
	free_arg(*head);
	*head = NULL;
	return (NULL);
}

char	*quotes(char *tmp, char **line, t_meg *shell, t_arg **head)
{
	char	*str;
	int		i;

	str = *line;
	shell->quotes = 1;
	g_shell.s_quotes = 1;
	i = 0;
	if (*str == 34)
	{
		tmp = double_q(str, shell, tmp, &i);
		str += i;
	}
	else if (*str == 39)
	{
		tmp = single_q(str, tmp, &i);
		str += i;
	}
	if (*str == 0)
		return (error_q(&tmp, head));
	else
		str++;
	*line = str;
	shell->quotes = 0;
	return (tmp);
}
