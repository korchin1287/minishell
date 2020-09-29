/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 12:06:51 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/29 12:11:31 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <unistd.h>
# include "stdio.h"
# include "parser/parser.h"


pid_t process;
char *g_line;

typedef struct	s_costl
{
	char **content;
	struct s_costl *next;
}				t_costl;

typedef struct  s_shell
{
	t_list *lst_before_export;
	t_list *list_env;
	t_list_arg *list_arg;
	t_list_arg *tmp_arg;
	char	*HOME;
	char **str_path;
	int j;
	int flag_exit;
	int flag_cd;
	int fd[2];
	int savestdin;
	int sevestdout;
	int flag_redirect;
	int flag_command_bash_not;
	int flag_command_bash;
	int status;
	t_costl *costl;
}               t_shell;
pid_t process;
void ft_singnal();
void	ft_print_name();
int		ft_check_name(char *str, char check);
void ft_add_list_before_export(t_shell *shell);
t_list	*ft_lstnew2(char *content);
void    ft_command_export(t_shell *shell);
char		**make_str(t_list **list_env, int size);
char 	**ft_sort_mass(char **tmp);
void    ft_command_cd(t_shell *shell);
void    ft_command_env(t_shell *shell);
void    ft_command_echo(t_shell *shell);
void    ft_command_unset(t_shell *shell);
void    ft_command_bash(t_shell *shell);
void 		ft_list_clear_before(t_list **list_before_export);
int			ft_len_arg(t_shell *sherll, t_data *data, char *str, int *i);
int		ft_check_list_for_export(t_shell *shell, t_list **list, char *str);
int ft_unset(t_shell *shell, char **str, t_list **list);
int		ft_pork(t_shell *shell, char *path, char **env);
int   ft_read_info(t_shell *shell);
int ft_execve(t_shell *shell, char *path, char **env);
int    ft_make_with_pipe(t_shell *shell);
void command_minishell(t_shell *shell);
int		ft_what_command(t_shell *shell);
int    ft_make_with_left_redir(t_shell *shell);
int 	ft_cout_mas(char **str);
void	ft_lstadd_back3(t_costl **lst, t_costl *new);
t_costl	*ft_lstnew3(char **content);
t_costl	*ft_lstlast3(t_costl *lst);
void	ft_exitstatus(t_shell *shell, int flag_exit);
char	*ft_init_parse_line(t_shell *shell, t_data *data, char *line, int flag);
char		*ft_parse_line(t_shell *shell, char *line);
void		ft_parse_list_line(t_shell *shell, t_list_arg *list);
void		ft_parse_list(t_shell *shell, t_list_arg *list);
int    ft_make_with_redir(t_shell *shell);
void	ft_command_bash_help1(t_shell *shell, char **env);
int	ft_command_bash_help(t_shell *shell, char **env);

#endif