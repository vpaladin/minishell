/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:15:32 by vpaladin          #+#    #+#             */
/*   Updated: 2021/08/25 19:57:43 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_meg	*shell;
	char	*line;

	(void)argv;
	shell = &g_shell;
	if (argc != 1)
	{
		write(2, "ERROR: Invalid arguments!\n", 26);
		return (1);
	}
	init_megashell(shell, env);
	while (1)
	{
		mod_singnal();
		line = readline("minishell$> ");
		if (line == NULL)
		{
			ft_putstr_fd("\e[1A\e[12C" "exit\n", 2);
			exit(0);
		}
		add_history(line);
		parse_and_execute(line);
		free(line);
	}
	return (0);
}
