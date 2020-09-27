/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 15:10:46 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/27 15:21:04 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_condition_check(t_data *data, char *str, int *i, int flag_cond)
{
	if (flag_cond == 0 && str[*i] == '\\' && str[*i + 1] != '\0' && (str[*i + 1] == '>' || str[*i + 1] == '<' || str[*i + 1] == '|' || str[*i + 1] == ';') && (str[*i - 1] != '\'' || str[*i - 1] != '\"'))
		return (1);
	//if (str[*i] == '\\' && str[*i + 1] != '\0' && (str[*i + 1] == '>' || str[*i + 1] == '<' || str[*i + 1] == '|' || str[*i + 1] == ';') && (str[*i - 1] != '\'' || str[*i - 1] != '\"'))
	if (flag_cond == 1 && str[*i] != '\0' && str[*i] != '>' && str[*i] != ';' && str[*i] != '|' && str[*i] != '<')
		return (1);
	//if (str[*i] != '\0' && str[*i] != '>' && str[*i] != ';' && str[*i] != '|' && str[*i] != '<')
	return (0);
}