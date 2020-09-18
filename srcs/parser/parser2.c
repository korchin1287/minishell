/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 10:08:03 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/17 19:22:13 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_len_qoutes_list(t_data *data, char *str, char c, int *i)
{
	int len;

	len = 0;
	while (str[*i] != c && str[*i] != '\0')
	{
		if (str[*i] == '\\' && (str[*i + 1] == '$' || str[*i + 1] == '\"' || str[*i + 1] == '`' || str[*i + 1] == '\\') && c != '\'')
		{
			
			len++;
			*i += 2;
		}
		else if (str[*i] == '$' && ((i && str[*i-1] != '\\') || i == 0) && str[*i + 1] != '\0' && str[*i + 1] != '?' && str[*i + 1] != '\\' && c != '\'')
		{
			len +=ft_len_dollars(str, data->before_export, data->env, *i);
			*i += ft_strlen_2(&str[*i + 1],  "\\$\'\"<;>| ") + 1;
		}
		else
		{
			len++;
			(*i)++;
		}
	}
	(*i)++;
	return (len);
}

int ft_len_arg_list(t_data *data, char *str, int *i)
{
	int len;
	int tmp;

	len = 0;
	while (str[*i] != ' ' && str[*i] != '\0')
	{
		if (str[*i] == '\\' && str[*i + 1] != '\0')
		{
			*i += 2;
			len++;
			if (str[*i])
				data->parser.flag_disable_dollar = 1;
		}
		else if (str[*i] == '\'' || str[*i] == '\"')
		{
			(*i)++;
			len += ft_len_qoutes_list(data, str, str[*i - 1], i);
		}
		else if (str[*i] == '$' && ((i && str[*i-1] != '\\') || i == 0) && str[*i + 1] != '\0' && str[*i + 1] != '?' && str[*i + 1] != '\'' && str[*i + 1] != '\"')
		{
			len +=ft_len_dollars(str, data->before_export, data->env, *i);
			*i += ft_strlen_2(&str[*i + 1],  "\\$\'\"<;>| ") + 1;
		}	
		
		else
		{
			(*i)++;
			len++;
		}
	}
	return (len);
}
int ft_check_char_qual(char *str, int k)
{
	int i;
	int l;

	i = k;
	l = 0;
	
	if (k == 0)
		return (0);
	while (str[--i] != ' ' && i >= 0)
		if (ft_isalpha(str[i]))
			l++;
	if (!l)
		return (0);
	i = k;
	while (str[--i] != ' ' && i >=0)
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]))
			return (0);
	}
	
	return 1;	
}
int	ft_qoutes(t_data *data, char *tmp, char *str, int *l)
{
	char c;
	int i;

	i = 1;
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
			str[i + 1] != '\0' && str[i + 1] != '?' &&
			str[i + 1] != '\\' && c != '\'')
			i += ft_dollar(data, &str[i], tmp, l);
		else
		{
			if (str[i] == '=')
				(*data->list)->flag_disable_char = 1;
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
			if (str[*i] == '=')
				(*data->list)->flag_disable_char = 1;
			tmp[l++] = str[(*i)++];
		}
		else if (str[*i] == '\'' || str[*i] == '\"')
			*i += ft_qoutes(data, tmp, &str[*i], &l);
		else if (str[*i] == '$' && ((i && str[*i-1] != '\\') || i == 0) &&
			str[*i + 1] != '\0' && str[*i + 1] != '?' &&
			str[*i + 1] != '\'' && str[*i + 1] != '\"' && str[*i + 1])
			*i += ft_dollar(data, &str[*i], tmp, &l);
		else
		{
			if (str[*i] == '=')
				if (!ft_check_char_qual(str, *i))
					(*data->list)->flag_disable_char = 1;
			tmp[l++] = str[(*i)++];
		}
	}
}

char *ft_parse_arg_list(t_data *data, char *str, int len, int i)
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
	ft_parse_arg_loop_list(data, str, tmp, &i);
	// if (str[i] == '>' || str[i] == ';' || str[i] == '|' || str[i] == '<')
	// {
	// 	if (len)
	// 		ft_add_end(&data->arg_list, ft_add(data, tmp));
	// 	else
	// 		ft_flag_add(data, &data->arg_list);
	// 	data->parser.count_arg = ft_size_list(data->arg_list);
	// 	tmp2 = make_map(&data->arg_list, data->parser.count_arg);
	// 	ft_add_lst_end(data->list, ft_add_lst(data, data->arg_list, tmp2));
	// 	ft_clear_list(&data->arg_list);
	// 	ft_flag_null(data);
	// }
	// else
	ft_add_end(&data->arg_list, ft_add(data, tmp));
	free(tmp);
	return (str);
}

char 		**ft_parse_list_line(t_list *lst_before_export, t_list *list_env, t_list_arg **list, char *str)
{
	t_data data;
	int i;
	int k;
	char **out;

	i = 0;
	k = 0;
	data.arg_list = NULL;
	data.list = list;
	data.env = list_env;
	data.before_export = lst_before_export;
	while (str[i] != '\0')
	{
		k = i;
		if ((ft_parse_arg_list(&data, str, ft_len_arg_list(&data, str, &i), k) == NULL))
		{
			ft_clear_list(&data.arg_list);
			return NULL;
		}
		i = ft_space(str, i);
	}
	i = ft_size_list(data.arg_list);
	out = make_map(&data.arg_list, i);
	ft_clear_list(&data.arg_list);
	free(str);
	return (out);
}

void	ft_parse_list(t_list_arg *list, t_list *lst_before_export, t_list *list_env)
{
	int i;

	i = -1;
	list->arg = ft_parse_list_line(lst_before_export, list_env, &list, list->arg[0]);
// 	while (list)
// 	{
// 		i = -1;
// 		while(list->arg[++i])
// 			printf("%s\n", list->arg[i]);
// 		printf("pipe              %d\n", list->flag_pipe);
// 		printf("command end       %d\n", list->flag_end);
// 		printf("one redirect      %d\n", list->flag_redir_one);
// 		printf("two redirect 	  %d\n", list->flag_redir_two);
// 		printf("reverse redirect  %d\n", list->flag_redir_one_left);
// 		printf("disable char '='  %d\n", list->flag_disable_char);
// 		printf("disable char '$'  %d\n", list->flag_disable_dollar);
// 		list = list->next;
// 	}
// 	exit(0);
}
