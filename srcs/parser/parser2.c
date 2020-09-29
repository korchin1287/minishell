/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 10:08:03 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/29 20:16:39 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"





int	ft_qoutes(t_data *data, char *tmp, char *str, int *l)
{
	char c;
	int i;
	int k;

	i = 1;
	k = i;
	c = str[0];
	while (str[i] != c && str[i] != '\0')
	{
		if (str[i] == '\\' && (str[i + 1] == '$' || str[i + 1] == '\"' ||
			str[i + 1] == '`' || str[i + 1] == '\\') && c != '\'')
		{
			i += 1;
			tmp[(*l)++] = str[(i)++];
		}
		else if (str[i] == '$' && ((i && str[i-1] != '\\') || i == 0) &&
			str[i + 1] != '\0' &&
			str[i + 1] != '\\' && str[i + 1] != '\"' && c != '\'')
			i += ft_dollar(data, &str[i], tmp, l);
		else
		{
			if (str[i] == '=' && ft_search_char_equal_before_space_or_qoute(str, i, 1))
				if (!ft_check_char_qual(data, str, i, c))
					(*data->list)->flag_disable_char = ft_size_list(data->arg_list) + 1;
			tmp[(*l)++] = str[(i)++];
		}
	}
	return (++i);
}


void ft_parse_arg_loop_list(t_data *data, char *str, char *tmp, int *i)
{
	int		l;

	l = 0;
	while (str[*i] != ' ' && str[*i] != '\0')
	{
		if (str[*i] == '\\' && str[*i + 1] != '\0')
		{
			*i += 1;
			if (str[*i] == '=' && ft_check_cmd(data->arg_list) && ft_search_char_equal_before_space_or_qoute(str, *i, 0))
				(*data->list)->flag_disable_char = ft_size_list(data->arg_list) + 1;
			tmp[l++] = str[(*i)++];
		}
		else if (ft_condition_check(data, str, i, 3))
			*i += ft_dollar(data, "$HOME", tmp, &l);
		else if (str[*i] == '\'' || str[*i] == '\"')
			*i += ft_qoutes(data, tmp, &str[*i], &l);
		else if (ft_condition_check(data, str, i, 2))
			*i += ft_dollar(data, &str[*i], tmp, &l);
		else
		{
			if (ft_condition_check(data, str, i, 4))
				if (!ft_check_char_qual(data, str, *i, '\0'))
					(*data->list)->flag_disable_char = ft_size_list(data->arg_list) + 1;
			tmp[l++] = str[(*i)++];
		}
	}
}

char	*ft_parse_arg_list(t_data *data, char *str, int len, int i)
{
	char *out;
	char **tmp2;
	int l;

	l = 0;
	if ((out = (char *)malloc(sizeof(char*) * (len + 1))) == NULL)
		exit(0);
	ft_bzero(out, len);
	ft_parse_arg_loop_list(data, str, out, &i);
	ft_add_end(&data->arg_list, ft_add(data, out));
	ft_flag_null(data);
	ft_free_null(out);
	return (str);
}

void	ft_parse_list_line(t_shell *shell, t_list_arg *list)
{
	t_data data;
	int i;
	int k;
	char **out;

	char *c;
	i = 0;
	k = 0;
	list->arg[0] = ft_init_parse_line(shell, &data, list->arg[0], 1);
	data.list = &list;
	while (list->arg[0][i] != '\0')
	{
		k = i;
		ft_parse_arg_list(&data, list->arg[0], ft_len_arg_list(&data, list->arg[0], &i), k);
		if (i == 17)
			c = &list->arg[0][i];
		i = ft_space(list->arg[0], i);
		c = &list->arg[0][i];

		
	}
	if (i == 0)
		ft_add_end(&data.arg_list, ft_add(&data, ""));
	i = ft_size_list(data.arg_list);
	out = make_map(&data.arg_list, i);
	ft_clear_list(&data.arg_list);
	ft_free_null(list->arg[0]);
	list->arg = out;
}
