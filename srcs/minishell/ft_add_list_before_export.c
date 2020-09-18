/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_list_before_export.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 17:26:44 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/18 19:11:43 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void 		ft_list_clear_before(t_list **list_before_export)
{
	t_list *tmp;

	while (*list_before_export)
	{
		tmp = *list_before_export;
		*list_before_export = (*list_before_export)->next;
		free(tmp->content);
		free(tmp);
		tmp = NULL;	
	}
}

static int	ft_check_args_be(t_shell *shell)
{
	char **tmp;
	int i;
	int j;
	
	j = shell->j;
	tmp = shell->list_arg->arg;
	while (tmp[j])
	{
		i = 0;
		while (tmp[j][i] != '\0')
		{
			if (tmp[j][i] == '=' && shell->list_arg->flag_disable_char == 0)
				break;
			if (tmp[j][i] != '=' && shell->list_arg->flag_disable_char == 0 && tmp[j][i + 1] == '\0')
				return (j);
			i++;
		}
		j++;
	}
	return (0);
}

void ft_add_list_before_export(t_shell *shell)
{
	int i;
	char **tmp;
	
	i = 0;

	if (shell->list_arg->arg[0] && !ft_check_args_be(shell))
	{
		tmp = shell->list_arg->arg;
		while (tmp[shell->j])
		{
			i = 0;
			while (tmp[shell->j][i] != '\0')
			{
				if (tmp[shell->j][i] == '=' && shell->list_arg->flag_disable_char == 0)
				{
					ft_lstadd_back(&shell->lst_before_export, ft_lstnew2(tmp[shell->j]));
					break;
				}
				if (tmp[shell->j][i] != '=' && shell->list_arg->flag_disable_char == 0 && tmp[shell->j][i + 1] == '\0')
					return;
				i++;
			}
			shell->j++;
		}
	}
	else
		shell->j = ft_check_args_be(shell);
}