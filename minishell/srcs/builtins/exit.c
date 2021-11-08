/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:03:51 by lverkart          #+#    #+#             */
/*   Updated: 2021/08/24 17:31:08 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check(char **str, int *sign)
{
	char	*temp;

	temp = *str;
	if (*temp == '-')
	{
		*sign = 1;
		temp++;
	}
	if (*temp == '+')
		temp++;
	if (ft_strlen(temp) > 19)
		return (0);
	*str = temp;
	return (1);
}

int	check_len(char *str)
{
	long long int	nb;
	long long int	max;
	long long int	min;
	int				sign;

	sign = 0;
	if (check(&str, &sign) == 0)
		return (0);
	nb = 0;
	max = 223372036854775807;
	min = 223372036854775808;
	if (ft_strncmp(str, "9", 1) == 0)
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			nb = nb * 10 + *str - '0';
			str++;
		}
		if (nb > max && sign == 0)
			return (0);
		else if (nb > min)
			return (0);
	}
	return (1);
}

unsigned int	cod_da_vinchi(long long int nb, char *str)
{
	unsigned int	tmp;

	if (ft_strcmp("-9223372036854775808", str) == 0)
		return (0);
	tmp = (unsigned int)nb;
	if (tmp > 255)
		while (tmp > 255)
			tmp -= 256;
	return (tmp);
}

int	exit_helper(t_meg *shell)
{
	long long int	exit_code;

	if (shell->argument[2] != NULL)
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		g_shell.exit_code = 1;
		return (1);
	}
	if (check_len(shell->argument[1]) == 1)
	{
		exit_code = ft_atoi(shell->argument[1]);
		exit_code = (long long)cod_da_vinchi(exit_code, shell->argument[1]);
		shell->exit_code = exit_code;
		if (shell->flag_pip_last != 0 || shell->flag_pip_next != 0)
			return (1);
		ft_putendl_fd("exit", 2);
		exit(shell->exit_code);
	}
	return (0);
}

void	ft_exit(t_meg *shell)
{
	int				size;

	size = 0;
	while (shell->argument[++size] != NULL)
		;
	if (size == 1)
	{
		if (shell->flag_pip_last != 0 || shell->flag_pip_next != 0)
		{
			g_shell.exit_code = 1;
			return ;
		}
		ft_putendl_fd("exit", 2);
		exit(shell->exit_code);
	}
	else if (ft_is_digits(shell->argument[1]) == 1)
		if (exit_helper(shell) == 1)
			return ;
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(shell->argument[1], 2);
	ft_putendl_fd(" numeric argument required", 2);
	shell->exit_code = 255;
	if (shell->flag_pip_last != 0 || shell->flag_pip_next != 0)
		return ;
	exit(shell->exit_code);
}
