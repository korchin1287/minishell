/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_null_parser1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 14:39:11 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/27 14:55:08 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_qoutes_null(t_data *data)
{
	data->parser.flag_close_quotes = 0;
	data->parser.flag_open_quotes = 0;
	data->parser.flag_single_quotes = 0;
	data->parser.flag_double_quotes = 0;
}

void	ft_flag_null(t_data *data)
{
	data->parser.flag_close_quotes = 0;
	data->parser.flag_open_quotes = 0;
	data->parser.flag_single_quotes = 0;
	data->parser.flag_double_quotes = 0;
	
	data->parser.flag_redir_one = 0;
	data->parser.flag_redir_two = 0;
	data->parser.flag_redir_one_left = 0;
	
	data->parser.flag_end = 0;
	data->parser.flag_pipe = 0;

	data->parser.count_arg = 0;
	data->parser.flag_disable_char = 0;
	data->parser.flag_disable_dollar = 0;
}

char	*ft_init_parse_line(t_shell *shell, t_data *data, char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	data->arg_list = NULL;
	data->list = &shell->list_arg;
	data->env = shell->list_env;
	data->before_export = shell->lst_before_export;
	ft_flag_null(data);
	line = ft_strtrim(line, " \t");
	ft_check_open_qoutes(data, line, &i);
	tmp = line;
	line = ft_check_close_qoutes(data, line, &i);
	free(tmp);
	ft_flag_null(data);
	return (line);
}