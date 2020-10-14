/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 12:47:52 by ndreadno          #+#    #+#             */
/*   Updated: 2020/10/13 17:40:57 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_end_parser_line(t_data *data)
{
	char		**var;
	int			count;
	t_list_arg	*tmp_struct;

	if (data->arg_list)
	{
		count = ft_size_list(data->arg_list);
		var = make_map(&data->arg_list, count);
		tmp_struct = ft_add_lst(data, var);
		ft_add_lst_end(data->list, tmp_struct);
		ft_clear_list(&data->arg_list);
		ft_flag_null(data);
	}
}

int			ft_qoutes_line(t_data *data, char *str, int *l)
{
	char	c;
	char	q;
	int		i;

	i = 1;
	c = str[0];
	data->out[(*l)++] = str[0];
	while (str[i] != c && str[i] != '\0')
	{
		q = str[i];
		if (str[i] == '\\' && (str[i + 1] == '$' ||
			str[i + 1] == '\"' || str[i + 1] == '`' ||
				str[i + 1] == '\\') && c != '\'')
		{
			data->out[(*l)++] = str[(i)++];
			data->out[(*l)++] = str[(i)++];
		}
		else
			data->out[(*l)++] = str[(i)++];
	}
	data->out[(*l)++] = str[(i)++];
	return (i);
}

void		ft_parse_arg_loop(t_data *data, char *str, int *i)
{
	int	l;

	l = 0;
	while (ft_condition_check(str, i, 1))
	{
		if (ft_condition_check(str, i, 0))
		{
			data->out[l++] = str[(*i)++];
			data->out[l++] = str[(*i)++];
		}
		else if (str[*i] == '\'' || str[*i] == '\"')
			*i += ft_qoutes_line(data, &str[*i], &l);
		else
			data->out[l++] = str[(*i)++];
	}
}

char		*ft_parse_arg(t_data *data, char *str, int len, int i)
{
	int		l;

	if (len == -1)
		return (NULL);
	l = 0;
	data->out = (char *)ft_malloc(sizeof(char*), len + 1);
	ft_bzero(data->out, len);
	ft_parse_arg_loop(data, str, &i);
	if (!ft_parse_redirect_pipe(data, str, len, i))
	{
		ft_flag_null(data);
		ft_add_end(&data->arg_list, ft_add(data, data->out));
	}
	ft_free_null((void **)&data->out);
	return (str);
}

char		*ft_parse_line(t_shell *shell, char *line)
{
	int		i;
	int		k;
	int		len;
	t_data	data;

	i = 0;
	k = 0;
	len = 0;
	line = ft_init_parse_line(shell, &data, line);
	i = ft_space(line, i);
	while (line[i] != '\0')
	{
		k = i;
		len = ft_len_arg(shell, &data, line, &i);
		if ((ft_parse_arg(&data, line, len, k) == NULL))
		{
			ft_clear_list(&data.arg_list);
			ft_clear_lst(data.list);
			ft_free_null((void **)&line);
			return (NULL);
		}
		i = ft_space(line, i);
	}
	ft_end_parser_line(&data);
	return (line);
}
