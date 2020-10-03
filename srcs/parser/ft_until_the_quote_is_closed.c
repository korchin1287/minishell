/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_until_the_quote_is_closed.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:12:43 by ndreadno          #+#    #+#             */
/*   Updated: 2020/10/02 17:24:05 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*ft_until_the_quote_is_closed(t_data *data, char *str, int *i)
{
	char *line;
	char *tmp;

	if (data->parser.flag_single_quotes == 1 ||
		data->parser.flag_double_quotes == 1)
	{
		tmp = str;
		write(1, "> ", 2);
		ft_get_next_line(0, &line);
		str = ft_strjoin(str, "\n");
		ft_free_null((void **)&tmp);
		tmp = str;
		str = ft_strjoin(str, line);
		ft_free_null((void **)&tmp);
		ft_check_open_qoutes(data, str, i);
		ft_free_null((void **)&line);
		return (ft_check_close_qoutes(data, str, i));
	}
	return (str);
}
