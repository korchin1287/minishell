/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 12:47:52 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/12 16:37:01 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**make_map(t_tmp_list **map, int size)
{
	char	**str;
	int		i;
	t_tmp_list	*tmp;

	if (!(str = malloc(sizeof(char *) * (size + 1))))
		exit(-1);
	i = 0;
	tmp = *map;
	while (tmp)
	{
		str[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

void ft_clear_list(t_tmp_list **head)
{
	t_tmp_list *tmp;

	
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->str);
		tmp->str = NULL;
		free(tmp);
		tmp = NULL;
		
	}
}
t_tmp_list	*ft_add(t_data *data, char *str)
{
	t_tmp_list *new;

	new = (t_tmp_list *)malloc(sizeof(t_tmp_list));
	if (new == NULL)
	{
		// vars->parse.erorrs.flag_malloc_error = 1;
		// ft_errors(vars);
	}
	new->str = str;
	new->next = NULL;
	return (new);
}

void		ft_add_end(t_tmp_list **start, t_tmp_list *new)
{
	t_tmp_list *tmp;

	tmp = *start;
	if (tmp == NULL)
	{
		(*start) = new;
		return;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
int ft_size_list(t_tmp_list *start)
{
	t_tmp_list	*tmp;
	int		i;

	i = 0;
	tmp = start;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return i;
}

void ft_quotes_null(t_data *data)
{
	data->parser.flag_close_quotes = 0;
	data->parser.flag_open_quotes = 0;
	data->parser.flag_single_quotes = 0;
	data->parser.flag_double_quotes = 0;
}

void ft_init(t_data *data)
{
	data->parser.flag_close_quotes = 0;
	data->parser.flag_open_quotes = 0;
	data->parser.flag_single_quotes = 0;
	data->parser.flag_single_quotes_count = 0;
	data->parser.flag_double_quotes = 0;
	data->parser.flag_double_quotes_count = 0;
	data->echo.flag_n = 0;
	data->arg_list = NULL;
	data->parser.count_arg = 0;
	data->echo_flag = 0;
}

void ft_check_open_qoutes(t_data *data, char *str, int *i)
{
	int k = *i;
	while (str[*i])
	{
		if (str[*i] == '\"' && !data->parser.flag_single_quotes)
		{
			if(*i != 0 && str[*i - 1] == '\\')
			{
				continue;
				(*i)++;
			}
			if (!data->parser.flag_double_quotes)
				k = *i + 1;
			data->parser.flag_double_quotes = data->parser.flag_double_quotes ? 0 : 1;
			data->parser.flag_double_quotes_count++;
		}
		if (str[*i] == '\'' && !data->parser.flag_double_quotes)
		{
			if(*i != 0 && str[*i - 1] == '\\')
			{
				continue;
				(*i)++;
			}
			if(!data->parser.flag_single_quotes)
				k = *i + 1;
			data->parser.flag_single_quotes = data->parser.flag_single_quotes ? 0 : 1;
			data->parser.flag_single_quotes_count++;
		}
		(*i)++;
	}
	*i = k;
}

char  *ft_check_close_qoutes(t_data *data, char *str, int *i)
{
	char *s;
	int k;
	char c = str[*i];
	char q;

	k = *i;
	while (str[*i] != '\0')
	{
		if (str[*i] == '\'' && data->parser.flag_single_quotes == 1)
		{
			if (str[*i - 1] == '\\')
			{
				(*i)++;
				continue;
			}
			if (data->parser.flag_single_quotes_count % 2 == 0)
			{
				data->parser.flag_close_quotes = 1;
				(*i)++;
			}
		}
		if (str[*i] == '\"' && data->parser.flag_double_quotes == 1)
		{
			if (str[*i - 1] == '\\')
			{
				(*i)++;
				continue;
			}
			if (data->parser.flag_double_quotes_count % 2 == 0)
			{
				data->parser.flag_close_quotes = 1;
				(*i)++;
			}
		}
		(*i)++;
	}
	if (data->parser.flag_close_quotes != 1)
	{
		*i = k;
		char *line;
		if (data->parser.flag_single_quotes == 1)
		{
			
			write(1, "quote> ", ft_strlen("quote> "));
			ft_get_next_line(0, &line);
			str = ft_strjoin(str, "\\n");
			str = ft_strjoin(str, line);
			ft_check_open_qoutes(data, str, i);
			return (ft_check_close_qoutes(data, str, i));
		}
		if (data->parser.flag_double_quotes == 1)
		{
			write(1, "dquote> ", ft_strlen("dquote> "));
			ft_get_next_line(0, &line);
			str = ft_strjoin(str, "\\n");
			str = ft_strjoin(str, line);
			ft_check_open_qoutes(data, str, i);
			return (ft_check_close_qoutes(data, str, i));
		}
	}
	return (str);
}

// char *trim_qoutes(t_data *data, char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (data->parser.flag_single_quotes == 1 && str[i] == '\'')
// 		{}
// 	}
// }

char *ft_string(t_data *data, char *str, int *i)
{
	int k;
	char *s;

	k = *i;
	while (str[*i])
	{
		if (str[*i] == ' ')
			break;
		if (str[*i] == ';' || str[*i] == '|')
		{
			data->parser.flag_arg = str[*i];
			data->parser.arg = 1;
			break;
		}	
		(*i)++;
	}
	s = ft_substr(str, k, *i - k);
	if (data->parser.flag_open_quotes != 1)
		s = ft_strtrim_char(s, '\'');
	*i = ft_space(str, *i);
	return s;
	
}

char *ft_qoutes(t_data *data, char *str, int *i)
{
	char *s;
	int k;
	char c = str[*i];
	char q;

	k = *i;
	while (str[*i] != '\0')
	{
		if (str[*i] == '\'' && data->parser.flag_single_quotes == 1)
		{
			if (str[*i - 1] == '\\')
			{
				(*i)++;
				continue;
			}
			if(str[*i + 1] == '\0' || str[*i + 1] == ' ')
				data->parser.flag_close_quotes = 1;
			break;
		}
		if (str[*i] == '\"' && data->parser.flag_double_quotes == 1)
		{
			if (str[*i - 1] == '\\')
			{
				(*i)++;
				continue;
			}
			if(str[*i + 1] == '\0' || str[*i + 1] == ' ')
				data->parser.flag_close_quotes = 1;
			break;
		}
		(*i)++;
	}
	if (data->parser.flag_close_quotes != 1)
	{
		*i = k;
		return (NULL);
	}
	q = str[*i];
	s = ft_substr(str, k , *i - k);
	if (str[*i] == '\"' || str[*i] == '\'' )
		(*i)++;
	*i = ft_space(str, *i);
	return (s);
}

char **ft_parse_line(t_list_arg *list, char *line)
{
	char *str;
	char *tmp;
	char **s;
	int i;
	t_data data;
	ft_init(&data);
	i = 0;
	str = ft_strtrim(line, " \t");
	ft_check_open_qoutes(&data, str, &i);
	str = ft_check_close_qoutes(&data, str, &i);
	ft_quotes_null(&data);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			if (i == 0 || str[i - 1] == ' ')
				data.parser.flag_single_quotes = 1;
		}
		if (str[i] == '\"')
		{
			if (i == 0 || str[i - 1] == ' ')
				data.parser.flag_double_quotes = 1;
		}
		if (data.parser.flag_single_quotes != 1 && data.parser.flag_double_quotes != 1)
		{
			if ((tmp = ft_string(&data, str, &i)))
				ft_add_end(&data.arg_list, ft_add(&data, tmp));
		}
		if (data.parser.flag_single_quotes == 1 || data.parser.flag_double_quotes == 1)
		{
			data.parser.flag_open_quotes = 1;
			i++;
			if ((tmp = ft_qoutes(&data, str, &i)))
				ft_add_end(&data.arg_list, ft_add(&data, tmp));
			ft_quotes_null(&data);
		}
		// if (data.parser.arg == 1)
		// {
		// 	ft_lstadd_back(&list, ft_lstnew());
		// }
		
	}
	data.parser.count_arg = ft_size_list(data.arg_list);
	s = make_map(&data.arg_list, data.parser.count_arg);
	
	// exit(0);
	
	// while (data.arg_list)
	// {
	// 	printf("%s\n", data.arg_list->str);
	// 	data.arg_list = data.arg_list->next;
	// }
	//ft_clear_list(&data.arg_list);
	return (s);
}