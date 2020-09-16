/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close_qoutes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 12:51:12 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/15 23:18:03 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_open_qoutes(t_data *data, char *str, int *i)
{
	int k = *i;
	while (str[*i])
	{
		if (str[*i] == '\"' && !data->parser.flag_single_quotes)
		{
			if(*i != 0 && str[*i - 1] == '\\')
			{
				(*i)++;
				continue;
			}
			if (!data->parser.flag_double_quotes)
				k = *i + 1;
			data->parser.flag_double_quotes = data->parser.flag_double_quotes ? 0 : 1;
			data->parser.flag_double_quotes_count++;
		}
		if (str[*i] == '\'' && !data->parser.flag_double_quotes)
		{
			if (*i && str[*i - 1] == '\\')
			{
				(*i)++;
				continue;
			}
			if(!data->parser.flag_single_quotes)
				k = *i + 1;
			data->parser.flag_single_quotes = data->parser.flag_single_quotes ? 0 : 1;
			data->parser.flag_single_quotes_count++;
		}
		(*i)++;
	}
	*i = k;
}

char	*ft_check_close_qoutes(t_data *data, char *str, int *i)
{
	char *s;
	int k;
	char c = str[*i];
	char q;

	k = *i;
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
		if (str[*i] == '\"' && data->parser.flag_double_quotes == 1)
		{
			if (*i && str[*i - 1] == '\\')
			{
				(*i)++;
				continue;
			}
			if (data->parser.flag_double_quotes_count % 2 == 0)
			{
				data->parser.flag_close_quotes = 1;
				(*i)++;
			}
		}
		(*i)++;
	}
	if (data->parser.flag_close_quotes != 1)
	{
		*i = k;
		char *line;
		if (data->parser.flag_single_quotes == 1)
		{
			
			write(1, "quote> ", ft_strlen("quote> "));
			ft_get_next_line(0, &line);
			str = ft_strjoin(str, "\n");
			str = ft_strjoin(str, line);
			ft_check_open_qoutes(data, str, i);
			return (ft_check_close_qoutes(data, str, i));
		}
		if (data->parser.flag_double_quotes == 1)
		{
			write(1, "dquote> ", ft_strlen("dquote> "));
			ft_get_next_line(0, &line);
			str = ft_strjoin(str, "\n");
			str = ft_strjoin(str, line);
			ft_check_open_qoutes(data, str, i);
			return (ft_check_close_qoutes(data, str, i));
		}
	}
	return (str);
}