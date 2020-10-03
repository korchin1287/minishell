/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 10:08:03 by ndreadno          #+#    #+#             */
/*   Updated: 2020/10/03 17:53:20 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**ft_end_parse2(t_data *data)
{
	int		i;
	char	**out;

	i = 0;
	i = ft_size_list(data->arg_list);
	out = make_map(&data->arg_list, i);
	ft_clear_list(&data->arg_list);
	return (out);
}

char		*ft_parse_arg_list(t_data *data, char *str, int len, int i)
{
	int		l;

	l = 0;
	if ((data->out = (char *)malloc(sizeof(char*) * (len + 1))) == NULL)
		exit(0);
	ft_bzero(data->out, len);
	ft_parse_arg_loop_list(data, str, &i);
	ft_add_end(&data->arg_list, ft_add(data, data->out));
	ft_flag_null(data);
	ft_free_null((void **)&data->out);
	return (str);
}

void		ft_parse_list_line(t_shell *shell, t_list_arg **list)
{
	t_data	data;
	int		i;
	int		k;
	int		len;
	char	*tmp;

	i = 0;
	k = 0;
	ft_init_parse(shell, &data);
	// data->arg_list = NULL;
	// data->list = &shell->list_arg;
	// data->env = shell->list_env;
	// data->before_export = shell->lst_before_export;
	// ft_flag_null(data);
	data.list = list;
	while ((*list)->arg[0][i] != '\0')
	{
		k = i;
		len = ft_len_arg_list(&data, (*list)->arg[0], &i);
		ft_parse_arg_list(&data, (*list)->arg[0], len, k);
		i = ft_space((*list)->arg[0], i);
	}
	if (i == 0)
		ft_add_end(&data.arg_list, ft_add(&data, ""));
	ft_free_str(&(*list)->arg);
	(*list)->arg = ft_end_parse2(&data);
}
