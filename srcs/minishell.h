/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 12:06:51 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/17 11:25:51 by ndreadno         ###   ########.fr       */
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

int			ft_pork(char *s, char *path, char **str, char **env);
#endif