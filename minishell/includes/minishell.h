/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaladin <vpaladin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 16:49:54 by lverkart          #+#    #+#             */
/*   Updated: 2021/08/25 19:10:10 by vpaladin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include "libft.h"
# include <dirent.h>

# define ERROR_DEL_CD "cd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory\n"

typedef struct s_list_env
{
	char				*name;
	char				*value;
	char				*line;
	int					print;
	int					alpha;
	int					equal;
	struct s_list_env	*next;
}	t_env;

typedef struct s_megashell
{
	t_env		*t_env;
	char		**argument;
	char		**build;
	char		**path;
	char		*pwd;
	char		**new_env;
	int			flag_pip_next;
	int			flag_pip_last;
	int			flag_op_fd;
	int			original_fd0;
	int			original_fd1;
	int			original_fd2;
	int			pipe;
	int			rpipe;
	int			exit_code;
	int			flag_dollar;
	int			quotes;
	int			s_quotes;
	int			destroy;
	int			inviz_export;
	int			flag_export;
	int			count_wait;
	int			flag_code_wait;
	int			will_not_build;
	int			if_null_lred;
}	t_meg;

t_meg	g_shell;

typedef struct s_arguments
{
	char				*arg;
	int					s_quotes;
	struct s_arguments	*next;
}	t_arg;

t_env	*create_env(char **env);
t_env	*ft_lstnew_env(char *env, int print);
int		ft_lstadd_env(t_env **lst, t_env *new);
void	init_megashell(t_meg *shell, char **env);
void	inport_env(t_meg *shell);
void	init_path(t_meg *shell);

int		parse_and_execute(char *line);
char	*env_var(t_meg *shell, char **line, char *tmp);
char	*quotes(char *tmp, char **line, t_meg *shell, t_arg **head);
int		redirect(char **line, t_arg **head);
int		open_pipe(char **line, char **tmp, t_arg **head);
int		execute(t_arg **head, char **tmp);
void	expectation(void);

int		valid_parse(t_meg *shell, t_arg **head, t_arg *arg, int i);
int		is_build_in(t_meg *shell);

int		ft_argsize(t_arg *lst);
void	ft_add_arg(t_arg **lst, t_arg *new);
t_arg	*ft_new_arg(char *content, int s_quotes);
char	**create_massiv(t_arg *head);

void	freedom(char **arg);
void	free_arg(t_arg *head);

void	mod_singnal(void);
void	defoult_singnal(void);
void	sig_in_redirect(void);

void	ft_error(char *name, int ex, int code);
int		valid_export_all(char *arg);
void	ft_if_head_NULL(void);

void	ft_unset(t_meg *shell, int i);
void	ft_echo(t_meg *shell, int i, int n);
void	ft_export_all(t_meg *shell, char **arg);
void	ft_cd(t_meg *shell);
void	ft_export(t_meg *shell);
void	ft_exit(t_meg *shell);
void	ft_pipex(t_meg *shell, int *fd);
void	build_in(t_meg *shell, int i, int *fd);

int		ft_valid_cmd(t_meg *shell, char *arg, int i, int flag);
int		redir_syntax_err(char *arg);
int		r_redirect(char *arg, t_meg *shell, int qoutes);
int		rr_redirect(char *arg, t_meg *shell, int qoutes);
int		l_redirect(char *arg, t_meg *shell, int qoutes);
int		ll_redirect(char *arg, t_meg *shell, int qoutes);
void	del_redirect(t_arg **head, t_arg **arg, int flag);
int		is_redirect(t_arg **head, t_arg **arg, t_meg *shell);
int		is_inv_export(t_arg *arg, t_meg *shell);
void	ft_add_front(t_arg **head, t_arg *arg, t_meg *shell);

#endif
