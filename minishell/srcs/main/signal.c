/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:15:50 by vpaladin          #+#    #+#             */
/*   Updated: 2021/08/24 13:33:31 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler_defoult(int signal)
{
	(void)signal;
	g_shell.flag_code_wait = 0;
	g_shell.exit_code = 130;
	write(2, "\n", 1);
}

static void	handler_mod(int signal)
{
	(void)signal;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_shell.exit_code = 1;
}

static void	quit(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit: 3\n", 2);
	g_shell.flag_code_wait = 0;
	g_shell.exit_code = 131;
}

void	defoult_singnal(void)
{
	signal(SIGINT, handler_defoult);
	signal(SIGQUIT, quit);
}

void	mod_singnal(void)
{
	signal(SIGINT, handler_mod);
	signal(SIGQUIT, SIG_IGN);
}
