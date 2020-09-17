/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 12:47:52 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/17 12:12:40 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_flag_add(t_data *data, t_tmp_list **new)
{
	if (!*new)
	{
		*new = (t_tmp_list *)malloc(sizeof(t_tmp_list));
		(*new)->str = NULL;
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

void ft_qoutes_null(t_data *data)
{
	data->parser.flag_close_quotes = 0;
	data->parser.flag_open_quotes = 0;
	data->parser.flag_single_quotes = 0;
	data->parser.flag_double_quotes = 0;
}

void ft_flag_null(t_data *data)
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

int	ft_qoutes_line(t_data *data, char *tmp, char *str, int *l)
{
	char c;
	int i;

	i = 1;
	c = str[0];
	tmp[(*l)++] = str[0];
	while (str[i] != c && str[i] != '\0')
	{
		// if (str[i] == '\\' && (str[i + 1] == '$' || str[i + 1] == '\"' ||
		// 	str[i + 1] == '`' || str[i + 1] == '\\') && c != '\'')
		// {
		// 	i += 1;
		// 	tmp[(*l)++] = str[(i)++];
		// }
		// else if (str[i] == '$' && ((i && str[i-1] != '\\') || i == 0) &&
		// 	str[i + 1] != '\0' && str[i + 1] != '?' &&
		// 	str[i + 1] != '\\' && c != '\'')
		// 	i += ft_dollar(data, &str[i], tmp, l);
		// else
		// {
		// 	if (str[i] == '=')
		// 		(*data->list)->flag_disable_char = 1;
			tmp[(*l)++] = str[(i)++];
		// }
	}
	tmp[(*l)++] = str[(i)++];
	return (i);
}
void ft_parse_arg_loop(t_data *data, char *str, char *tmp, int *i)
{
	int		l;

	l = 0;
	while (str[*i] != '\0' && str[*i] != '>' && str[*i] != ';'
		&& str[*i] != '|' && str[*i] != '<')
	{
		if (str[*i] == '\\' && str[*i + 1] != '\0' && (str[*i + 1] == '>' || str[*i + 1] == '<' || str[*i + 1] == '|' || str[*i + 1] == ';') && (str[*i - 1] != '\'' || str[*i - 1] != '\"'))
		{
			*i += 1;
			tmp[l++] = str[(*i)++];
		}
		else if (str[*i] == '\'' || str[*i] == '\"')
			*i += ft_qoutes_line(data, tmp, &str[*i], &l);
		// else if (str[*i] == '$' && ((i && str[*i-1] != '\\') || i == 0) &&
		// 	str[*i + 1] != '\0' && str[*i + 1] != '?' &&
		// 	str[*i + 1] != '\'' && str[*i + 1] != '\"' && str[*i + 1])
		// 	*i += ft_dollar(data, &str[*i], tmp, &l);
		else
			tmp[l++] = str[(*i)++];
	}
}

char *ft_parse_arg(t_data *data, char *str, int len, int i)
{
	char *tmp;
	char **tmp2;
	int l;

	if (len == -1)
		return (NULL);
	l = 0;
	if ((tmp = (char *)malloc(sizeof(char*) * (len + 1))) == NULL)
		exit(0);
	ft_bzero(tmp, len);
	ft_parse_arg_loop(data, str, tmp, &i);
	if (str[i] == '>' || str[i] == ';' || str[i] == '|' || str[i] == '<')
	{
		if (len)
			ft_add_end(&data->arg_list, ft_add(data, tmp));
		else
			ft_flag_add(data, &data->arg_list);
		data->parser.count_arg = ft_size_list(data->arg_list);
		tmp2 = make_map(&data->arg_list, data->parser.count_arg);
		ft_add_lst_end(data->list, ft_add_lst(data, data->arg_list, tmp2));
		ft_clear_list(&data->arg_list);
		ft_flag_null(data);
	}
	else
		ft_add_end(&data->arg_list, ft_add(data, tmp));
	free(tmp);
	return (str);
}



//------------------------len--------------------//
int ft_len_qoutes(t_data *data, char *str, char c, int *i)
{
	int len;

	len = 0;
	while (str[*i] != c && str[*i] != '\0')
	{
		// if (str[*i] == '\\' && (str[*i + 1] == '$' || str[*i + 1] == '\"' || str[*i + 1] == '`' || str[*i + 1] == '\\') && c != '\'')
		// {
			
		// 	len++;
		// 	*i += 2;
		// }
		// else if (str[*i] == '$' && ((i && str[*i-1] != '\\') || i == 0) && str[*i + 1] != '\0' && str[*i + 1] != '?' && str[*i + 1] != '\\' && c != '\'')
		// {
		// 	len +=ft_len_dollars(str, data->before_export, data->env, *i);
		// 	*i += ft_strlen_2(&str[*i + 1],  "\\$\'\"<;>| ") + 1;
		// }
		// else
		// {
			len++;
			(*i)++;
		// }
	}
	(*i)++;
	return (len);
}

int ft_len_arg(t_data *data, char *str, int *i)
{
	int len;
	int tmp;

	len = 0;
	while (str[*i] != '\0' && str[*i] != '>' && str[*i] != ';' && str[*i] != '|' && str[*i] != '<')
	{
		if (str[*i] == '\\' && str[*i + 1] != '\0' && (str[*i + 1] == '>' || str[*i + 1] == '<' || str[*i + 1] == '|' || str[*i + 1] == ';') && (str[*i - 1] != '\'' || str[*i - 1] != '\"'))
		{
			*i += 2;
			len++;
			// if (str[*i])
			// 	data->parser.flag_disable_dollar = 1;
		}
		else if (str[*i] == '\'' || str[*i] == '\"')
		{
			(*i)++;
			len += ft_len_qoutes(data, str, str[*i - 1], i) + 1;
		}
		// else if (str[*i] == '$' && ((i && str[*i-1] != '\\') || i == 0) && str[*i + 1] != '\0' && str[*i + 1] != '?' && str[*i + 1] != '\'' && str[*i + 1] != '\"')
		// {
		// 	len +=ft_len_dollars(str, data->before_export, data->env, *i);
		// 	*i += ft_strlen_2(&str[*i + 1],  "\\$\'\" <;>| ") + 1;
		// }	
		else
		{
			(*i)++;
			len++;
		}
	}
	if (str[*i] == '>' || str[*i] == '<' || str[*i] == ';' || str[*i] == '|')
	{
		if (!(tmp = ft_check_arg(data, str, str[*i], i)))
			return (-1);
	}
	return (len);
}



char 		**ft_parse_line(t_list *lst_before_export, t_list *list_env, t_list_arg **list, char *line)
{
	char *str;
	char **s;
	int i;
	int k;
	t_data data;

	i = 0;
	k = 0;
	data.arg_list = NULL;
	data.list = list;
	data.env = list_env;
	data.before_export = lst_before_export;
	ft_flag_null(&data);
	str = ft_strtrim(line, " \t");
	ft_check_open_qoutes(&data, str, &i);
	str = ft_check_close_qoutes(&data, str, &i);
	ft_flag_null(&data);

	i = 0;
	while (str[i] != '\0')
	{
		k = i;
		if ((ft_parse_arg(&data, str, ft_len_arg(&data, str, &i), k) == NULL))
		{
			ft_clear_list(&data.arg_list);
			ft_clear_lst(list);
			return NULL;
		}
		i = ft_space(str, i);
	}
		if (data.arg_list)
		{
			int q = ft_size_list(data.arg_list);
			s = make_map(&data.arg_list, q);
			ft_add_lst_end(list, ft_add_lst(&data, data.arg_list, s));
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