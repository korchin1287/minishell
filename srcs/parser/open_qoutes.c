/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_qoutes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 16:38:28 by ndreadno          #+#    #+#             */
/*   Updated: 2020/10/13 17:27:19 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_open_double_quotes(t_data *data, char *str, int *i, int *k)
{
	if (str[*i] == '\"' && !data->parser.flag_single_quotes)
	{
		if (*i != 0 && str[*i - 1] == '\\' && data->parser.flag_slash)
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
static int ft_check_open_single_qoutes(t_data *data, char *str, int *i, int *k)
{
	if (str[*i] == '\'' && !data->parser.flag_double_quotes)
	{
		if (!data->parser.flag_single_quotes)
			*k = *i + 1;
		data->parser.flag_single_quotes =
			data->parser.flag_single_quotes ? 0 : 1;
		data->parser.flag_single_quotes_count++;
	}
	return (0);
}
void		ft_check_open_qoutes(t_data *data, char *str, int *i)
{
	int k;

	k = *i;
	while (str[*i])
	{
		if (str[*i] == '\\' && str[*i + 1] == '\\')
		{
			data->parser.flag_slash = 0;
			*i += 2;
			continue;
		}
		if (ft_check_open_double_quotes(data, str, i, &k))
			continue;
		if (ft_check_open_single_qoutes(data, str, i, &k))
			continue;
		data->parser.flag_slash = 1;
		(*i)++;
	}
	data->parser.flag_close_quotes = data->parser.flag_single_quotes || data->parser.flag_double_quotes ? 0 : 1;
	*i = k;
}