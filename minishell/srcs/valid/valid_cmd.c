/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 13:43:02 by lverkart          #+#    #+#             */
/*   Updated: 2021/08/25 20:28:29 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_opendir(DIR *dirp, char *n, char *arg)
{
	struct dirent	*entry;

	entry = readdir(dirp);
	while (entry)
	{
		if (ft_strlen(n + 1) == ft_strlen(entry->d_name)
			&& !ft_strncmp(entry->d_name, n + 1, ft_strlen(arg)))
			return (0);
		entry = readdir(dirp);
	}
	return (1);
}

int	is_absalute_cmd(char *arg)
{
	DIR				*dirp;
	int				flag;
	char			*buf;
	char			*n;

	flag = 1;
	n = ft_strrchr(arg, '/');
	if (!n)
		return (1);
	n[0] = '\0';
	buf = ft_strdup(arg);
	dirp = opendir(buf);
	if (dirp)
		flag = ft_opendir(dirp, n, arg);
	n[0] = '/';
	free(buf);
	if (dirp)
		closedir(dirp);
	return (flag);
}

int	is_local_cmd(char *arg, t_meg *shell, int flag)
{
	DIR				*dirp;
	char			*buf;
	char			*n;
	char			*tmp;

	n = ft_strrchr(arg, '/');
	if (!n)
		return (1);
	n[0] = '\0';
	buf = ft_strjoin(shell->pwd, "/");
	tmp = buf;
	buf = ft_strjoin(buf, arg);
	free(tmp);
	dirp = opendir(buf);
	if (dirp)
		flag = ft_opendir(dirp, n, arg);
	n[0] = '/';
	free(buf);
	if (dirp)
		closedir(dirp);
	return (flag);
}

int	ft_valid_cmd(t_meg *shell, char *arg, int i, int flag)
{
	DIR				*dirp;
	struct dirent	*entry;

	flag = is_absalute_cmd(arg);
	if (flag == 1)
		flag = is_local_cmd(arg, shell, 1);
	while (flag && shell->path != NULL && shell->path[++i] != NULL)
	{
		dirp = opendir(shell->path[i]);
		if (dirp)
		{
			entry = readdir(dirp);
			while (entry && flag)
			{
				if (ft_strlen(arg) == ft_strlen(entry->d_name)
					&& !ft_strncmp(entry->d_name, arg, ft_strlen(arg)))
					flag = 0;
				entry = readdir(dirp);
			}
			closedir(dirp);
		}
	}
	if (flag)
		return (1);
	return (0);
}
