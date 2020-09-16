/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 12:06:51 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/16 13:48:34 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/errno.h>
# include <string.h>
# include "stdio.h"
# include "parser/parser.h"


// void ft_cd(t_minshl *shell, char *str);
// void ft_pwd(t_minshl *shell);
// void ft_env(t_minshl *shell);
// void ft_echo(t_minshl *shell, char *str, int flag);
t_list_arg	*ft_add_lst(t_data *data, t_tmp_list *tmp_list, char **str);
void 		ft_clear_lst(t_list_arg **head);
void		ft_add_lst_end(t_list_arg **start, t_list_arg *new);
char 		**ft_parse_line(t_list *lst_before_export, t_list *list_env, t_list_arg **list, char *line);
int			ft_pork(char *s, char *path, char **str, char **env);
#endif