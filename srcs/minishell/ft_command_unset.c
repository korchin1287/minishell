/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 18:11:39 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/26 18:07:50 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_shell *shell, char **str, t_list **list)
{
	t_list *tmp;
	t_list *tmp_2;
	int j;
	int check;

	j = 0;
	if (!*list)
		return (0);
	while (str[j])
	{
		int count = ft_strlen_3(str[j], '=');
		check = ft_check_name(str[j], '\0');
		tmp = *list;
		if (tmp && ft_strnstr(tmp->content, str[j], count) && check)
		{
			if (tmp->next)
				*list = tmp->next;
			else 
				*list = NULL;
			free(tmp->content);
			free(tmp);
			break ;
		}
		else if (!check)
		{
			write(2, "minishell: unset: `", 20);
			ft_putstr_fd(str[j], 2);
			write(2, "': not a valid identifier\n", 27);
			ft_make_wexitstatus(shell, 1);
		}
		else if (tmp->next)
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
		j++;
	}
	return (0);
}

void    ft_command_unset(t_shell *shell)
{
    shell->j++;
	ft_unset(shell, &shell->list_arg->arg[shell->j], &shell->lst_before_export);
	ft_unset(shell, &shell->list_arg->arg[shell->j], &shell->list_env);
}