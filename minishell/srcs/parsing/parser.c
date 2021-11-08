/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:15:39 by vpaladin          #+#    #+#             */
/*   Updated: 2021/08/25 17:28:16 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_argument(char **line, char *tmp, t_arg **head, int s_quotes)
{
	if (**line == '<' || **line == '>')
	{
		if (ft_strcmp(tmp, "") != 0)
			ft_add_arg(head, ft_new_arg(tmp, s_quotes));
		else
			free(tmp);
		if (redirect(line, head) != 0)
			return (0);
	}
	else if (tmp != NULL && g_shell.flag_dollar != 1)
		ft_add_arg(head, ft_new_arg(tmp, s_quotes));
	else
	{
		free(tmp);
		tmp = NULL;
	}
	return (1);
}

static int	end_parse(t_arg **head, char **tmp)
{
	int	status;

	if (*head == NULL)
	{
		if (*tmp)
			free(*tmp);
		return (0);
	}
	if (execute(head, tmp) == 2)
		return (0);
	while (g_shell.count_wait > 0)
	{
		waitpid(0, &status, 0);
		g_shell.count_wait--;
	}
	if (g_shell.flag_code_wait)
		g_shell.exit_code = WEXITSTATUS(status);
	return (0);
}

static void	init_parse(void)
{
	g_shell.flag_code_wait = 0;
	g_shell.flag_dollar = 0;
	g_shell.s_quotes = 0;
}

static int	parse(char **line, char **tmp, t_arg **head)
{
	while (**line != ' ' && **line != 0 && **line != '<' && **line != '>')
	{
		init_parse();
		if (**line == 34 || **line == 39)
		{
			*tmp = quotes(*tmp, line, &g_shell, head);
			if (*tmp == NULL)
				return (0);
		}
		else if (**line == '$')
			*tmp = env_var(&g_shell, line, *tmp);
		else if (**line == '|')
		{
			if (open_pipe(line, tmp, head) == 2)
				return (0);
			else
				break ;
		}
		else
		{
			*tmp = ft_str_addchar(*tmp, **line);
			(*line)++;
		}
	}
	return (1);
}

int	parse_and_execute(char *line)
{
	char	*tmp;
	t_arg	*head;

	if (*line == '\0')
		return (0);
	head = NULL;
	tmp = NULL;
	g_shell.destroy = 0;
	while (*line != 0 && g_shell.destroy == 0)
	{
		while (*line == ' ' && *line != 0)
			line++;
		if (*line == 0)
			break ;
		tmp = ft_strdup("");
		if (parse(&line, &tmp, &head) == 0)
			return (0);
		if (add_argument(&line, tmp, &head, g_shell.s_quotes) == 0)
			return (0);
	}
	return (end_parse(&head, &tmp));
}
