/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 12:06:51 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/21 18:33:50 by nofloren         ###   ########.fr       */
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
# include <dirent.h>
# include <unistd.h>
# include "stdio.h"
# include "parser/parser.h"

typedef struct  s_shell
{
	t_list *lst_before_export;
	t_list *list_env;
	t_list_arg *list_arg;
	t_list_arg *tmp_arg;
	int j;
	int flag_exit;
	int flag_cd;
	int fd1[2];
	int fd2[2];
}               t_shell;

void ft_add_list_before_export(t_shell *shell);
t_list	*ft_lstnew2(char *content);
void    ft_command_export(t_shell *shell);
char		**make_str(t_list **list_env, int size);
char 	**ft_sort_mass(char **tmp);
size_t	ft_strlen_3(const char *str, char c);
void    ft_command_cd(t_shell *shell);
void    ft_command_env(t_shell *shell);
void    ft_command_echo(t_shell *shell);
void    ft_command_unset(t_shell *shell);
void    ft_command_bash(t_shell *shell);
void 		ft_list_clear_before(t_list **list_before_export);
int		ft_check_list_for_export(t_shell *shell, t_list **list, char *str);
int	ft_unset(char **str, t_list **list);
int		ft_pork(t_shell *shell, char *path, char **env);

#endif