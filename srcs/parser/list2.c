#include "../minishell.h"

void		ft_clear_lst(t_list_arg **head)
{
	t_list_arg	*tmp;
	int			i;

	i = -1;
	while (*head)
	{
		i = -1;
		tmp = *head;
		*head = (*head)->next;
		ft_free_str(&tmp->arg);
		ft_free_str(&tmp->arg2);
		ft_free_null((void **)&tmp);
	}
}

char		**make_map(t_tmp_list **map, int size)
{
	char		**str;
	int			i;
	t_tmp_list	*tmp;

	str = (char **)ft_malloc(sizeof(char *), (size + 1));
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

void		ft_clear_list(t_tmp_list **head)
{
	t_tmp_list *tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		ft_free_null((void **)&tmp->str);
		tmp->str = NULL;
		ft_free_null((void **)&tmp);
		tmp = NULL;
	}
}
