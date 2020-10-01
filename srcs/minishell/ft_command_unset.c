/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 18:11:39 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/01 12:13:34 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset_help1(t_shell *shell, char **str, int j)
{
	write(2, "minishell: unset: `", 20);
	ft_putstr_fd(str[j], 2);
	write(2, "': not a valid identifier\n", 27);
	ft_exitstatus(shell, 1);
	str[j][0] = '\0';
}

int ft_unset(t_shell *shell, char **str, t_list **list)
{
	t_list *tmp;
	t_list *tmp_2;
	int j;
	int check;
	char c;

	j = 0;
	if (!*list)
		return (0);
	while (str[j])
	{
		int count = ft_strlen(str[j]);
		check = ft_check_name(str[j], '\0');
		tmp = *list;
		c = tmp->content[count];
		if (tmp && ft_strnstr(tmp->content, str[j], count) && check && (tmp->content[count] == '\0' || tmp->content[count] == '='))
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
			ft_unset_help1(shell, str, j);
		else if (tmp->next)
		{
			while (tmp->next)
			{
				if (ft_strnstr(tmp->next->content, str[j], count) && (tmp->next->content[count] == '\0' || tmp->next->content[count] == '='))
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
	int  *flag_notvalid;

    shell->j++;
	ft_exitstatus(shell, 0);
	ft_unset(shell, &shell->list_arg->arg[shell->j], &shell->lst_before_export);
	ft_unset(shell, &shell->list_arg->arg[shell->j], &shell->list_env);
}