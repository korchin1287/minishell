/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_qoutes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 12:51:12 by ndreadno          #+#    #+#             */
/*   Updated: 2020/10/15 16:53:27 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	ft_check_single_close_qoutes(t_data *data, char *str, int *i)
{
	if (str[*i] == '\'' && data->parser.flag_single_quotes == 1)
	{
		if (data->parser.flag_single_quotes_count % 2 == 0)
		{
			data->parser.flag_close_quotes = 1;
			(*i)++;
		}
	}
	return (0);
}

static int	ft_check_close_double_quotes(t_data *data, char *str, int *i)
{
	if (str[*i] == '\"' && data->parser.flag_double_quotes == 1)
	{
		if (*i && str[*i - 1] == '\\' && data->parser.flag_slash)
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

char		*ft_check_close_qoutes(t_data *data, char *str, int *i)
{
	int k;

	k = *i;
	str = ft_strdup(str);
	while (str[*i] != '\0')
	{
		if (str[*i] == '\\' && str[*i + 1] == '\\')
		{
			*i += 2;
			data->parser.flag_slash = 0;
			continue;
		}
		if (ft_check_single_close_qoutes(data, str, i))
			continue;
		if (ft_check_close_double_quotes(data, str, i))
			continue;
		data->parser.flag_slash = 1;
		(*i)++;
	}
	if (data->parser.flag_close_quotes != 1)
		return (ft_until_the_quote_is_closed(data, &str, &k));
	return (str);
}
