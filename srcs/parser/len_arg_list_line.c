/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_arg_list_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:51:56 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/29 20:15:45 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_len_qoutes_list(t_data *data, char *str, char c, int *i)
{
	int len;
		char q;
	len = 0;
	q = str[*i];
	(*i)++;
	q = str[*i];
	while (str[*i] != c && str[*i] != '\0')
	{
		q = str[*i];
		if (str[*i] == '\\' && (str[*i + 1] == '$' || str[*i + 1] == '\"' || str[*i + 1] == '`' || str[*i + 1] == '\\') && c != '\'')
		{
			len++;
			*i += 2;
		}
		else if (str[*i] == '$' && ((i && str[*i-1] != '\\') || i == 0) && str[*i + 1] != '\0' && str[*i + 1] != '\\' && str[*i + 1] != '\"' && c != '\'')
		{
			len +=ft_len_dollars(str, data->before_export, data->env, *i);
			*i += ft_count_dollar(&str[*i + 1]) + 1;
		}
		else
		{
			len++;
			(*i)++;
		}
		q = str[*i];
	}
	(*i)++;
	return (len);
}

int ft_len_arg_list(t_data *data, char *str, int *i)
{
	int len;
	int tmp;

	len = 0;
	while (str[*i] != ' ' && str[*i] != '\0')
	{
		if (str[*i] == '\\' && str[*i + 1] != '\0')
		{
			*i += 2;
			len++;
			if (str[*i])
				data->parser.flag_disable_dollar = 1;
		}
		else if (ft_condition_check(data, str, i, 3))
		{
			len += ft_len_dollars("$HOME", data->before_export, data->env, 0);
			*i += ft_count_dollar("HOME") + 1;
		}
		else if (str[*i] == '\'' || str[*i] == '\"')
			len += ft_len_qoutes_list(data, str, str[*i], i);
		else if (ft_condition_check(data, str, i, 2))
		{
			len +=ft_len_dollars(str, data->before_export, data->env, *i);
			*i += ft_count_dollar(&str[*i + 1]) + 1;
		}		
		else
		{
			(*i)++;
			len++;
		}
	}
	return (len);
}