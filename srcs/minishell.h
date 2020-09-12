/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 12:06:51 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/12 16:36:52 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <sys/errno.h>
# include <string.h>
# include "stdio.h"
# include "parser.h"

typedef struct s_list_arg
{
	void *content;
	char flag;
	struct s_list *new_list;
	struct s_list *next;
}t_list_arg;


// void ft_cd(t_minshl *shell, char *str);
// void ft_pwd(t_minshl *shell);
// void ft_env(t_minshl *shell);
// void ft_echo(t_minshl *shell, char *str, int flag);
char **ft_parse_line(t_list_arg *list, char *line);
int		ft_pork(char *s, char *path, char **str, char **env);
#endif