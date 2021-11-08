/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:15:28 by vpaladin          #+#    #+#             */
/*   Updated: 2021/08/25 15:52:58 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*ft_new_arg(char *content, int s_quotes)
{
	t_arg	*ret;

	ret = malloc(sizeof(t_arg));
	if (!ret)
		return (NULL);
	if (s_quotes == 1)
		ret->s_quotes = s_quotes;
	else
		ret->s_quotes = 0;
	ret->arg = content;
	ret->next = NULL;
	return (ret);
}

char	**create_massiv(t_arg *head)
{
	int		count;
	int		i;
	char	**arg;

	count = ft_argsize(head);
	arg = malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (i < count)
	{
		arg[i] = ft_strdup(head->arg);
		head = head->next;
		i++;
	}
	arg[i] = NULL;
	return (arg);
}

void	ft_add_arg(t_arg **lst, t_arg *new)
{
	t_arg	*buf;

	if (!new || !lst)
		return ;
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
}

int	ft_argsize(t_arg *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
