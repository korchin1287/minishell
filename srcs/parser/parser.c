/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 12:47:52 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/27 15:50:43 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_qoutes_line(t_data *data, char *str, int *l)
{
	char c;
	int i;

	i = 1;
	c = str[0];
	data->out[(*l)++] = str[0];
	while (str[i] != c && str[i] != '\0')
			data->out[(*l)++] = str[(i)++];
	data->out[(*l)++] = str[(i)++];
	return (i);
}

void ft_parse_arg_loop(t_data *data, char *str, int *i)
{
	int		l;

	l = 0;
	while (ft_condition_check(data, str, i, 1))
	{
		if (ft_condition_check(data, str, i, 0))
		{
			*i += 1;
			data->out[l++] = str[(*i)++];
		}
		else if (str[*i] == '\'' || str[*i] == '\"')
			*i += ft_qoutes_line(data, &str[*i], &l);
		else
			data->out[l++] = str[(*i)++];
	}
}

char *ft_parse_arg(t_data *data, char *str, int len, int i)
{
	char	**tmp2;
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
	free(data->out);
	return (str);
}

char 		**ft_parse_line(t_shell *shell, char *line)
{
	char *str;
	char **s;
	int i;
	int k;
	t_data data;

	i = 0;
	k = 0;
	str = ft_init_parse_line(shell, &data, line);
	while (str[i] != '\0')
	{
		k = i;
		if ((ft_parse_arg(&data, str, ft_len_arg(&data, str, &i), k) == NULL))
		{
			ft_clear_list(&data.arg_list);
			ft_clear_lst(data.list);
			return NULL;
		}
		i = ft_space(str, i);
	}
	if (data.arg_list)
	{
		ft_add_lst_end(data.list,
			ft_add_lst(&data, data.arg_list,
			make_map(&data.arg_list,
				ft_size_list(data.arg_list))));
		ft_clear_list(&data.arg_list);
		ft_flag_null(&data);
	}
	i = -1;
	
	// while (*list)
	// {
	// 	i = -1;
	// 	while((*list)->arg[++i])
	// 		printf("%s\n", (*list)->arg[i]);
	// 	printf("pipe              %d\n", (*list)->flag_pipe);
	// 	printf("command end       %d\n", (*list)->flag_end);
	// 	printf("one redirect      %d\n", (*list)->flag_redir_one);
	// 	printf("two redirect 	  %d\n", (*list)->flag_redir_two);
	// 	printf("reverse redirect  %d\n", (*list)->flag_redir_one_left);
	// 	printf("disable char '='  %d\n", (*list)->flag_disable_char);
	// 	printf("disable char '$'  %d\n", (*list)->flag_disable_dollar);
	// 	*list = (*list)->next;
	// }
	// exit(0);
	// // printf("%s\n", s[0]);
	//ft_clear_list(&data.arg_list);
	return (s);
}