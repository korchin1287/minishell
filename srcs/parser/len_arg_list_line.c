/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_arg_list_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:51:56 by ndreadno          #+#    #+#             */
/*   Updated: 2020/10/13 11:52:39 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_return_len_qoutes(t_data *data, char *str, int *i, char c)
{
	int len;

	len = 0;
	if (str[*i] == '\\' && (str[*i + 1] == '$' ||
		str[*i + 1] == '\"' || str[*i + 1] == '`' ||
			str[*i + 1] == '\\') && c != '\'')
	{
		len++;
		*i += 2;
	}
	else if (ft_condition_check(str, i, 2) && c != '\'')
	{
		len += ft_len_dollars(str, data->before_export, data->env, *i);
		*i += ft_count_dollar(&str[*i + 1]) + 1;
	}
	else if (ft_condition_check2(str, *i, '\0', 8) && c != '\'')
		len += ft_len_status(i);
	else
	{
		len++;
		(*i)++;
	}
	return (len);
}

int			ft_len_qoutes_list(t_data *data, char *str, char c, int *i)
{
	int len;

	len = 0;
	(*i)++;
	while (str[*i] != c && str[*i] != '\0')
		len += ft_return_len_qoutes(data, str, i, c);
	(*i)++;
	return (len);
}

static void	ft_return_len(t_data *data, char *str, int *i, int *len)
{
	if (str[*i] == '\\' && str[*i + 1] != '\0')
	{
		*i += 2;
		(*len)++;
	}
	else if (ft_condition_check(str, i, 3))
	{
		*len += ft_len_dollars("$HOME", data->before_export, data->env, 0);
		*i += ft_count_dollar("HOME") + 1;
	}
	else if (str[*i] == '\'' || str[*i] == '\"')
		*len += ft_len_qoutes_list(data, str, str[*i], i);
	else if (ft_condition_check(str, i, 2) ||
		ft_condition_check2(str, *i, '\0', 7))
	{
		*len += ft_len_dollars(str, data->before_export, data->env, *i);
		*i += ft_count_dollar(&str[*i + 1]) + 1;
	}
	else if (ft_condition_check2(str, *i, '\0', 8))
		*len += ft_len_status(i);
	else
	{
		(*i)++;
		(*len)++;
	}
}

int			ft_len_arg_list(t_data *data, char *str, int *i)
{
	int len;

	len = 0;
	while (str[*i] != ' ' && str[*i] != '\0')
		ft_return_len(data, str, i, &len);
	return (len);
}
