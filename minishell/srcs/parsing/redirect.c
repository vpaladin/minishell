/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:15:39 by vpaladin          #+#    #+#             */
/*   Updated: 2021/08/25 19:31:53 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_red(char **tmp, char c, int i, t_arg **head)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	if (i > 4)
		i = 4;
	while (i-- > 2)
		ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	free(*tmp);
	g_shell.exit_code = 258;
	free_arg(*head);
	*head = NULL;
	expectation();
	ft_if_head_NULL();
	return (1);
}

int	redirect(char **line, t_arg **head)
{
	int		i;
	char	*tmp;
	char	*str;
	char	c;

	i = 0;
	str = *line;
	tmp = ft_strdup("");
	c = *str;
	while (str[i] == c)
	{
		tmp = ft_str_addchar(tmp, *str);
		i++;
	}
	if (i > 2)
		return (error_red(&tmp, c, i, head));
	ft_add_arg(head, ft_new_arg(tmp, 0));
	*line = str + i;
	return (0);
}
