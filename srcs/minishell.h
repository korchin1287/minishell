/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 12:06:51 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/25 20:23:26 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/errno.h>
# include <string.h>
# include <sys/types.h>
# include <errno.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <unistd.h>
# include "stdio.h"
# include "parser/parser.h"


pid_t process;

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
	int j;
	int flag_exit;
	int flag_cd;
	int fd[2];
	int savestdin;
	int sevestdout;
	int flag_redirect;
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
int		ft_check_list_for_export(t_shell *shell, t_list **list, char *str);
int	ft_unset(char **str, t_list **list);
int		ft_pork(t_shell *shell, char *path, char **env);
int   ft_read_info(t_shell *shell);
void ft_execve(t_shell *shell, char *path, char **env);
int    ft_make_with_pipe(t_shell *shell);
void command_minishell(t_shell *shell);
int		ft_what_command(t_shell *shell);
int    ft_make_with_left_redir(t_shell *shell);
int 	ft_cout_mas(char **str);
void	ft_lstadd_back3(t_costl **lst, t_costl *new);
t_costl	*ft_lstnew3(char **content);
t_costl	*ft_lstlast3(t_costl *lst);

#endif