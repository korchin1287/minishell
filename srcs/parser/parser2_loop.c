/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 15:16:07 by ndreadno          #+#    #+#             */
/*   Updated: 2020/10/04 12:52:31 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_loop_qoutes(t_data *data, char *str, int *l, char c)
{
	int i;

	i = 1;
	while (str[i] != c && str[i] != '\0')
	{
		if (ft_condition_check2(str, i, c, 5))
		{
			i += 1;
			data->out[(*l)++] = str[(i)++];
		}
		else if (ft_condition_check(str, &i, 2) && c != '\'')
			i += ft_dollar(data, &str[i], data->out, l);
		else
		{
			if (ft_condition_check2(str, i, c, 6))
				if (!ft_check_char_qual(data, str, i, c))
					(*data->list)->flag_disable_char =
						ft_size_list(data->arg_list) + 1;
			data->out[(*l)++] = str[(i)++];
		}
	}
	return (i);
}

int			ft_qoutes(t_data *data, char *str, int *l)
{
	char	c;
	int		i;

	i = 0;
	c = str[0];
	i = ft_loop_qoutes(data, str, l, c);
	return (++i);
}

static void	ft_check_back_slash(t_data *data, char *str, int *i, int *l)
{
	*i += 1;
	if (str[*i] == '=' && ft_check_cmd(data->arg_list) &&
			ft_search_char_equal_before_space_or_qoute(str, *i, 0))
		(*data->list)->flag_disable_char = ft_size_list(data->arg_list) + 1;
	data->out[(*l)++] = str[(*i)++];
}

static int	ft_write_tmp(t_data *data, char *str, int *i, int *l)
{
	if (str[*i] == '\\' && str[*i + 1] != '\0')
		ft_check_back_slash(data, str, i, l);
	else if (ft_condition_check(str, i, 3))
		*i += ft_dollar(data, "$HOME", data->out, l);
	else if (str[*i] == '\'' || str[*i] == '\"')
		*i += ft_qoutes(data, &str[*i], l);
	else if (ft_condition_check(str, i, 2))
		*i += ft_dollar(data, &str[*i], data->out, l);
	else
	{
		if (ft_condition_check(str, i, 4))
			if (!ft_check_char_qual(data, str, *i, '\0'))
				(*data->list)->flag_disable_char =
					ft_size_list(data->arg_list) + 1;
		data->out[(*l)++] = str[(*i)++];
	}
	return (*l);
}

void		ft_parse_arg_loop_list(t_data *data, char *str, int *i)
{
	int		l;

	l = 0;
	while (str[*i] != ' ' && str[*i] != '\0')
		ft_write_tmp(data, str, i, &l);
}
