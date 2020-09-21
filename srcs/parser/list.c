/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 12:45:04 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/21 19:57:14 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		str[i] = !tmp->str ? NULL : ft_strdup(tmp->str);
		tmp = tmp->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

void 		ft_clear_list(t_tmp_list **head)
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

void 		ft_clear_lst(t_list_arg **head)
{
	t_list_arg *tmp;
	int i;

	i = -1;
	while (*head)
	{
		i = -1;
		tmp = *head;
		*head = (*head)->next;
		while (tmp->arg[++i])
			free(tmp->arg[i]);
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
	new->str = ft_strdup(str);
	new->flag_redir_one = data->parser.flag_redir_one;
	new->flag_redir_two = data->parser.flag_redir_two;
	new->flag_redir_one_left = data->parser.flag_redir_one_left;
	new->flag_end = data->parser.flag_end;
	new->flag_pipe = data->parser.flag_pipe;
	new->flag_disable_char = data->parser.flag_disable_char;
	new->flag_disable_dollar = data->parser.flag_disable_dollar;
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

t_list_arg *ft_add_lst(t_data *data, t_tmp_list *tmp_list, char **str)
{
	t_list_arg *new;
	
	new = (t_list_arg *)malloc(sizeof(t_list_arg));
	if (!new)
		exit(-1);
	new->arg = str;
	new->flag_redir_one = data->parser.flag_redir_one;
	new->flag_redir_two = data->parser.flag_redir_two;
	new->flag_redir_one_left = data->parser.flag_redir_one_left;
	new->flag_end = data->parser.flag_end;
	new->flag_pipe = data->parser.flag_pipe;
	new->flag_disable_char = data->parser.flag_disable_char;
	new->flag_disable_dollar = data->parser.flag_disable_dollar;
	new->next = NULL;
	return (new);
}

void		ft_add_lst_end(t_list_arg **start, t_list_arg *new)
{
	t_list_arg *tmp;

	tmp = *start;
	if (tmp == NULL)
	{
		(*start) = new;
		return;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	tmp->back = tmp;
	//tmp->back = tmp->back ? tmp : NULL;
}

int			ft_size_list(t_tmp_list *start)
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
	return (i);
}