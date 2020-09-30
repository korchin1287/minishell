/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect_and_pipe.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 15:27:46 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/30 17:03:22 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_flag_add(t_data *data, t_tmp_list **new)
{
	if (!*new)
	{
		*new = (t_tmp_list *)ft_malloc(sizeof(t_tmp_list), 1);
		(*new)->str = ft_strdup("");
		data->parser.flag_disable_char = 1;
		(*new)->next = NULL;
	}
	(*new)->flag_redir_one = data->parser.flag_redir_one;
	(*new)->flag_redir_two = data->parser.flag_redir_two;
	(*new)->flag_redir_one_left = data->parser.flag_redir_one_left;
	(*new)->flag_end = data->parser.flag_end;
	(*new)->flag_pipe = data->parser.flag_pipe;
	(*new)->flag_disable_char = data->parser.flag_disable_char;
	(*new)->flag_disable_char = data->parser.flag_disable_dollar;
}

int		ft_parse_redirect_pipe(t_data *data, char *str, int len, int i)
{
	char **tmp;

	if (str[i] == '>' || str[i] == ';' || str[i] == '|' || str[i] == '<')
	{
		if (len)
			ft_add_end(&data->arg_list, ft_add(data, data->out));
		else
			ft_flag_add(data, &data->arg_list);
		data->parser.count_arg = ft_size_list(data->arg_list);
		tmp = make_map(&data->arg_list, data->parser.count_arg);
		ft_add_lst_end(data->list, ft_add_lst(data, data->arg_list, tmp));
		ft_clear_list(&data->arg_list);
		ft_flag_null(data);
		return (1);
	}
	return (0);
}
