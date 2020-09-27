/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:20:50 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/27 12:43:31 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		while (tmp->arg[++i])
			free(tmp->arg[i]);
		free(tmp);
		tmp = NULL;
	}
}

char		**make_map(t_tmp_list **map, int size)
{
	char		**str;
	int			i;
	t_tmp_list	*tmp;

	str = ft_malloc(sizeof(char *), (size + 1));
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

void		ft_clear_list(t_tmp_list **head)
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
