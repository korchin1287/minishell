/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 12:47:52 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/30 15:23:46 by ndreadno         ###   ########.fr       */
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
		tmp_struct = ft_add_lst(data, data->arg_list, var);
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
		if (str[i] == '\\' && (str[i + 1] == '$' || str[i + 1] == '\"' || str[i + 1] == '`' || str[i + 1] == '\\') && c != '\'')
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
	while (ft_condition_check(data, str, i, 1))
	{
		if (ft_condition_check(data, str, i, 0))
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
	ft_free_null(data->out);
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
	line = ft_init_parse_line(shell, &data, line, 0);
	int w = ft_strlen(line);
	int a = ft_strlen("echo hello ");
	int d = ft_strlen(" t2 world ");
	int x = ft_strlen(" t3 \"echo dhjsfjh ' \\' \"\\\"\" \"$PWD~\\; echo -e");
	int z = ft_strlen("");
	while (line[i] != '\0')
	{
		k = i;
		len = ft_len_arg(shell, &data, line, &i);
		if (i == 24)
			i = i;
		if ((ft_parse_arg(&data, line, len, k) == NULL))
		{
			ft_clear_list(&data.arg_list);
			ft_clear_lst(data.list);
			return (NULL);
		}
		i = ft_space(line, i);
	}
	ft_end_parser_line(&data);
	// while (shell->list_arg)
	// {
	// 	printf("%s\n", shell->list_arg->arg[0]);
	// 	printf("%d\n",shell->list_arg->flag_end);
	// 	printf("%d\n",shell->list_arg->flag_pipe);
	// 	printf("%d\n",shell->list_arg->flag_redir_one);
	// 	printf("%d\n",shell->list_arg->flag_redir_two);
	// 	printf("%d\n",shell->list_arg->flag_redir_one_left);
	// 	printf("%d\n",shell->list_arg->flag_disable_char);
	// 	shell->list_arg = shell->list_arg->next;
	// }
	// exit(0);
	return (line);
}
