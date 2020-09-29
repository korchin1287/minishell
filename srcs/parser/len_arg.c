/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 15:24:23 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/28 17:29:38 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_len_qoutes(t_data *data, char *str, char c, int *i)
{
	int len;

	len = 0;
	(*i)++;
	while (str[*i] != c && str[*i] != '\0')
	{
		len++;
		(*i)++;
	}
	(*i)++;
	return (len);
}

int ft_len_arg(t_shell *shell, t_data *data, char *str, int *i)
{
	int len;
	int tmp;

	len = 0;
	


	while (ft_condition_check(data, str, i, 1))
	{
		if (ft_condition_check(data, str, i, 0))
		{
			*i += 2;
			len++;
		}
		else if (str[*i] == '\'' || str[*i] == '\"')
			len += ft_len_qoutes(data, str, str[*i - 1], i) + 1;
		else
		{
			(*i)++;
			len++;
		}
	}
	if (str[*i] == '>' || str[*i] == '<' || str[*i] == ';' || str[*i] == '|')
	{
		if (!(tmp = ft_check_arg(data, str, str[*i], i)))
		{
			ft_exitstatus(shell, 258);
			return (-1);
		}
	}
	return (len);
}