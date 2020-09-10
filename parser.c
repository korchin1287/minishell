/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 12:47:52 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/10 14:01:07 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**make_map(t_list **map, int size)
{
	char	**str;
	int		i;
	t_list	*tmp;

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

void ft_clear_list(t_list **head)
{
	t_list *tmp;

	
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
t_list	*ft_add(t_data *data, char *str)
{
	t_list *new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
	{
		// vars->parse.erorrs.flag_malloc_error = 1;
		// ft_errors(vars);
	}
	new->str = str;
	new->next = NULL;
	return (new);
}

void		ft_add_end(t_list **start, t_list *new)
{
	t_list *tmp;

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
int ft_size_list(t_list *start)
{
	t_list	*tmp;
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
	data->parser.flag_double_quotes = 0;
	data->echo.flag_n = 0;
	data->arg_list = NULL;
	data->parser.count_arg = 0;
	data->echo_flag = 0;
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
			data->parser.flag_close_quotes = 1;
			break;
		}
		if (str[*i] == '\"' && data->parser.flag_double_quotes == 1)
		{
			data->parser.flag_close_quotes = 1;
			break;
		}
		(*i)++;
	}
	if (data->parser.flag_close_quotes != 1)
		return NULL;
	q = str[*i];
	s = ft_substr(str, k , *i - k);
	*i = ft_space(str, *i + 1);
	return (s);
}
char *ft_string(t_data *data, char *str, int *i)
{
	int k;
	char *s;

	k = *i;
	while (str[*i])
	{
		if (str[*i] == ' ')
			break;	
		(*i)++;
	}
	s = ft_substr(str, k, *i - k);
	s = ft_strtrim_new(s, "\"'");
	*i = ft_space(str, *i);
	return s;
	
}
char **ft_parse_line(char *line)
{
	char *str;
	char **s;
	int i;
	t_data data;

	ft_init(&data);
	i = 0;
	str = ft_strtrim(line, " \t");
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			data.parser.flag_single_quotes = 1;
		}
		if (str[i] == '\"')
		{
			data.parser.flag_double_quotes = 1;
		}
		if (data.parser.flag_single_quotes != 1 && data.parser.flag_double_quotes != 1)
		{
			ft_add_end(&data.arg_list, ft_add(&data, ft_string(&data, str, &i)));
		}
		if (data.parser.flag_single_quotes == 1 ||data.parser.flag_double_quotes == 1)
		{
			i++;
			ft_add_end(&data.arg_list, ft_add(&data, ft_qoutes(&data, str, &i)));
			ft_quotes_null(&data);
		}
	}
	data.parser.count_arg = ft_size_list(data.arg_list);
	s = make_map(&data.arg_list, data.parser.count_arg);
	ft_clear_list(&data.arg_list);
	return (s);
	// while (data->arg_list)
	// {
	// 	printf("%s\n", data->arg_list->str);
	// 	data->arg_list = data->arg_list->next;
	// }
	// exit(0);
	// ft_check_command(data, &data->arg_list);
}