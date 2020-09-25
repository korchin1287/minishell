/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 10:08:03 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/24 21:18:47 by ndreadno         ###   ########.fr       */
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
			*i += ft_count_dollar(&str[*i + 1]) + 1;
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
		else if (str[*i] == '~' && (str[*i + 1] == '\0' || str[*i + 1] == ' '||
			str[*i + 1] == '/') && ((*i && str[*i - 1] == ' ') || (*i == 0)))
		{
			len += ft_len_dollars("$HOME", data->before_export, data->env, 0);
			*i += ft_count_dollar("HOME") + 1;
		}
		else if (str[*i] == '\'' || str[*i] == '\"')
		{
			(*i)++;
			len += ft_len_qoutes_list(data, str, str[*i - 1], i);
		}
		else if (str[*i] == '$' && ((i && str[*i-1] != '\\') || i == 0) && str[*i + 1] != '\0' &&
			str[*i + 1] != '?' && str[*i + 1] != '\'' && str[*i + 1] != '\"')
		{
			len +=ft_len_dollars(str, data->before_export, data->env, *i);
			*i += ft_count_dollar(&str[*i + 1]) + 1;
		}	
		
		else
		{
			(*i)++;
			len++;
		}
	}
	return (len);
}

int	ft_check_cmd(t_tmp_list *list)
{
	
	if (list)
		return (ft_strcmp(list->str, "export"));
	return (1);
}

int	ft_check_char_qual(t_data *data, char *str, int k, char flag)
{
	int i;
	int export;

	i = k;
	if (k == 0)
		return (0);
	i = k;
	export = ft_check_cmd(data->arg_list); 
	while (str[--i] != ' ' && i >=0)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && export)
			return (0);
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '\'' && str[i] != '\"' && export == 0)
			return (0);
		if (str[i] == '\'' && str[i] != flag)
			return (0);
		if (str[i] == '\"' && str[i] != flag)
			return (0);
	}
	if (ft_isalpha(str[i + 1]) == 0 && str[i + 1] != '_' && export != 0)
		return (0);
	if (!ft_isalnum(str[i + 1]) && str[i + 1] != '_' && str[i + 1] != '\'' && str[i + 1] != '\"' && export == 0)
			return (0);
	if (str[i + 1] == '\'' && str[i + 1] != flag)
			return (0);
	if (str[i + 1] == '\"' && str[i + 1] != flag)
			return (0);
	return 1;	
}

int ft_search_char_equal_before_space_or_qoute(char *str, int i, int flag)
{
	if (i == 0)
		return (1);
	while (--i >= 0)
	{
		if (str[i] == '=')
			return (0);
		if (str[i] == ' ' && !flag)
			return (1);	
	}
	return (1);
}

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
			str[i + 1] != '\0' && str[i + 1] != '?' &&
			str[i + 1] != '\\' && c != '\'')
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
		else if (str[*i] == '~' && (str[*i + 1] == '\0' || str[*i + 1] == ' '||
			str[*i + 1] == '/') && ((*i && str[*i - 1] == ' ') || (*i == 0)))
			*i += ft_dollar(data, "$HOME", tmp, &l);
		else if (str[*i] == '\'' || str[*i] == '\"')
			*i += ft_qoutes(data, tmp, &str[*i], &l);
		else if (str[*i] == '$' && ((i && str[*i-1] != '\\') || i == 0) &&
			str[*i + 1] != '\0' && str[*i + 1] != '?' &&
			str[*i + 1] != '\'' && str[*i + 1] != '\"' && str[*i + 1])
			*i += ft_dollar(data, &str[*i], tmp, &l);
		else
		{
			if (str[*i] == '=' && ft_search_char_equal_before_space_or_qoute(str, *i, 0))
				if (!ft_check_char_qual(data, str, *i, '\0'))
					(*data->list)->flag_disable_char = ft_size_list(data->arg_list) + 1;
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
	ft_add_end(&data->arg_list, ft_add(data, tmp));
	ft_flag_null(data);
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
	ft_flag_null(&data);
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
	// while (list)
	// {
	// 	i = -1;
	// 	while(list->arg[++i])
	// 		printf("%s\n", list->arg[i]);
	// 	printf("pipe              %d\n", list->flag_pipe);
	// 	printf("command end       %d\n", list->flag_end);
	// 	printf("one redirect      %d\n", list->flag_redir_one);
	// 	printf("two redirect 	  %d\n", list->flag_redir_two);
	// 	printf("reverse redirect  %d\n", list->flag_redir_one_left);
	// 	printf("disable char '='  %d\n", list->flag_disable_char);
	// 	printf("disable char '$'  %d\n", list->flag_disable_dollar);
	// 	list = list->next;
	// }
	// exit(0);
}
