/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 15:24:23 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/30 14:00:58 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_len_qoutes(t_data *data, char *str, char c, int *i)
{
	int len;
	char q;

	len = 0;
	(*i)++;
	while (str[*i] != c && str[*i] != '\0')
	{
		q = str[*i];
		if (str[*i] == '\\' && (str[*i + 1] == '$' || str[*i + 1] == '\"' || str[*i + 1] == '`' || str[*i + 1] == '\\') && c != '\'')
		{
			
			len++;
			*i += 2;
			
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

static int	ft_len_arg_loop(t_shell *shell, t_data *data, char *str, int *i)
{
	int len;
	char c;

	len = 0;
	while (ft_condition_check(data, str, i, 1))
	{
		c = str[*i];
		if (ft_condition_check(data, str, i, 0))
		{
			*i += 2;
			len += 2;
		}
		else if (str[*i] == '\'' || str[*i] == '\"')
			len += ft_len_qoutes(data, str, str[*i], i) + 2;
		else
		{
			(*i)++;
			len++;
		}
		c = str[*i];
	}
	c = str[*i];
	return (len);
}

int			ft_len_arg(t_shell *shell, t_data *data, char *str, int *i)
{
	int len;
	int tmp;

	len = ft_len_arg_loop(shell, data, str, i);
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
