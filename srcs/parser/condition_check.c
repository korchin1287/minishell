/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 15:10:46 by ndreadno          #+#    #+#             */
/*   Updated: 2020/10/04 12:51:41 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_condition_check(char *str, int *i, int flag_cond)
{
	if (flag_cond == 0 && str[*i] == '\\' && str[*i + 1] != '\0')
		return (1);
	if (flag_cond == 1 && str[*i] != '\0' && str[*i] != '>' &&
			str[*i] != ';' && str[*i] != '|' && str[*i] != '<')
		return (1);
	if (flag_cond == 2 && str[*i] == '$' &&
		((i && str[*i - 1] != '\\') || i == 0) && str[*i + 1] != '\0' &&
			str[*i + 1] != '\'' && str[*i + 1] != '\"' && str[*i + 1] != ' ')
		return (1);
	if (flag_cond == 3 && str[*i] == '~' &&
		(str[*i + 1] == '\0' || str[*i + 1] == ' ' || str[*i + 1] == '/') &&
			((*i && str[*i - 1] == ' ') || (*i == 0)))
		return (1);
	if (flag_cond == 4 && str[*i] == '=' &&
			ft_search_char_equal_before_space_or_qoute(str, *i, 0))
		return (1);
	return (0);
}
