/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 13:32:29 by vpaladin          #+#    #+#             */
/*   Updated: 2021/08/24 13:33:01 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_red(int signal)
{
	(void)signal;
	exit(2);
}

void	sig_in_redirect(void)
{
	signal(SIGINT, exit_red);
}
