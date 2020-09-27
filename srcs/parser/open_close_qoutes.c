/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close_qoutes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 12:51:12 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/27 14:05:18 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_open_double_quotes(t_data *data, char *str, int *i, int *k)
{
	if (str[*i] == '\"' && !data->parser.flag_single_quotes)
	{
		if (*i != 0 && str[*i - 1] == '\\')
		{
			(*i)++;
			return (1);
		}
		if (!data->parser.flag_double_quotes)
			*k = *i + 1;
		data->parser.flag_double_quotes =
			data->parser.flag_double_quotes ? 0 : 1;
		data->parser.flag_double_quotes_count++;
	}
	return (0);
}

static int	ft_check_close_double_quotes(t_data *data, char *str, int *i)
{
	if (str[*i] == '\"' && data->parser.flag_double_quotes == 1)
	{
		if (*i && str[*i - 1] == '\\')
		{
			(*i)++;
			return (1);
		}
		if (data->parser.flag_double_quotes_count % 2 == 0)
		{
			data->parser.flag_close_quotes = 1;
			(*i)++;
		}
	}
	return (0);
}

void		ft_check_open_qoutes(t_data *data, char *str, int *i)
{
	int k;

	k = *i;
	while (str[*i])
	{
		if (ft_check_open_double_quotes(data, str, i, &k))
			continue;
		if (str[*i] == '\'' && !data->parser.flag_double_quotes)
		{
			if (!data->parser.flag_single_quotes)
				k = *i + 1;
			data->parser.flag_single_quotes =
				data->parser.flag_single_quotes ? 0 : 1;
			data->parser.flag_single_quotes_count++;
		}
		(*i)++;
	}
	*i = k;
}

char		*ft_check_close_qoutes(t_data *data, char *str, int *i)
{
	int k;

	k = *i;
	str = ft_strdup(str);
	while (str[*i] != '\0')
	{
		if (str[*i] == '\'' && data->parser.flag_single_quotes == 1)
		{
			if (data->parser.flag_single_quotes_count % 2 == 0)
			{
				data->parser.flag_close_quotes = 1;
				(*i)++;
			}
		}
		if (ft_check_close_double_quotes(data, str, i))
			continue;
		(*i)++;
	}
	if (data->parser.flag_close_quotes != 1)
		return (ft_until_the_quote_is_closed(data, str, &k));
	return (str);
}
