/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 12:06:51 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/08 15:12:55 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <sys/errno.h>
# include <string.h>

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

typedef struct s_minshl
{
	t_echo echo;
	t_parser parser;
	t_list *arg_list;
	char **env;
	int cd_flag;
	int echo_flag;
}				t_minshl;

void ft_parse_line(t_minshl *shell, char *line);
void ft_cd(t_minshl *shell, char *str);
void ft_pwd(t_minshl *shell);
void ft_env(t_minshl *shell);
void ft_echo(t_minshl *shell, char *str, int flag);
#endif