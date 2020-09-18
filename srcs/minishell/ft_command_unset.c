/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 18:11:39 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/18 18:14:21 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **str, t_list **list)
{
	t_list *tmp;
	t_list *tmp_2;
	int j;

	j = 0;
	if (!*list)
		return (0);
	while (str[j])
	{
		int count = ft_strlen_3(str[j], ' ');

		tmp = *list;
		if (tmp->next)
		{
			while (tmp->next)
			{
				if (ft_strnstr(tmp->next->content, str[j], count))
				{
					tmp_2 = tmp->next;
					tmp->next = tmp->next->next;
					free(tmp_2->content);
					free(tmp_2);
					tmp_2= NULL;
					break ;
				}
				tmp = tmp->next;
			}
		}
		if (tmp && ft_strnstr(tmp->content, str[j], count))
		{
			free(tmp->content);
			free(tmp);
			*list = NULL;
			break ;
		}
		j++;
	}
	return (0);
}

void    ft_command_unset(t_shell *shell)
{
    shell->j++;
	ft_unset(&shell->list_arg->arg[shell->j], &shell->lst_before_export);
	ft_unset(&shell->list_arg->arg[shell->j], &shell->list_env);
}