#include "../minishell.h"

t_tmp_list	*ft_add(t_data *data, char *str)
{
	t_tmp_list *new;

	new = (t_tmp_list *)ft_malloc(sizeof(t_tmp_list), 1);
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
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

t_list_arg	*ft_add_lst(t_data *data, char **str)
{
	t_list_arg *new;

	new = (t_list_arg *)ft_malloc(sizeof(t_list_arg), 1);
	new->arg = str;
	new->arg2 = NULL;
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
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	tmp->next->back = tmp;
}

int			ft_size_list(t_tmp_list *start)
{
	t_tmp_list	*tmp;
	int			i;

	i = 0;
	tmp = start;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
