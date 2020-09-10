/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 12:06:51 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/10 12:01:11 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <sys/errno.h>
# include <string.h>
# include "stdio.h"
int flag_exit;
typedef struct s_echo
{
	int flag_n;
	int flag_V;
}t_echo;
typedef struct s_list
{
	char *str;
	struct s_list *next;
}t_list;

typedef struct s_parser
{
	int flag_open_quotes;
	int flag_close_quotes;
	int flag_single_quotes;
	int flag_double_quotes;	
	int count_arg;
	
}				t_parser;

typedef struct s_data
{
	t_echo echo;
	t_parser parser;
	t_list *arg_list;
	char **env;
	int cd_flag;
	int echo_flag;
}				t_data;

char **ft_parse_line(char *line);
void ft_init(t_data *data);
void		ft_add_end(t_list **start, t_list *new);
t_list	*ft_add(t_data *data, char *str);
void ft_clear_list(t_list **head);
// void ft_cd(t_minshl *shell, char *str);
// void ft_pwd(t_minshl *shell);
// void ft_env(t_minshl *shell);
// void ft_echo(t_minshl *shell, char *str, int flag);
int		ft_pork(char *s, char *path, char **str, char **env);
#endif