/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 18:11:39 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/03 16:12:41 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void		ft_unset_help1(t_shell *shell, char **str, int j)
{
	write(2, "minishell: unset: `", 20);
	ft_putstr_fd(str[j], 2);
	write(2, "': not a valid identifier\n", 27);
	ft_exitstatus(shell, 1);
	str[j][0] = '\0';
}

static void		ft_unset_help_2(t_list *tmp, char **str, int j, int count)
{
	t_list *tmp_2;

	while (tmp->next)
	{
		if (ft_strnstr(tmp->next->content, str[j], count) &&
			(tmp->next->content[count] == '\0' ||
			tmp->next->content[count] == '='))
		{
			tmp_2 = tmp->next;
			tmp->next = tmp->next->next;
			free(tmp_2->content);
			free(tmp_2);
			tmp_2 = NULL;
			break ;
		}
		tmp = tmp->next;
	}
}

static void		ft_unset_help_3(t_list *tmp, t_list **list)
{
	if (tmp->next)
		*list = tmp->next;
	else
		*list = NULL;
	ft_free_null((void **)&tmp->content);
	ft_free_null((void **)&tmp);
}

int				ft_unset(t_shell *shell, char **str, t_list **list)
{
	t_list	*tmp;
	int		j;
	int		check;
	int		count;

	j = -1;
	if (!*list)
		return (0);
	tmp = *list;
	while (str[++j])
	{
		count = ft_strlen(str[j]);
		check = ft_check_name(str[j], '\0');
		if (tmp && ft_strnstr(tmp->content, str[j], count) && check &&
			(tmp->content[count] == '\0' || tmp->content[count] == '='))
		{
			ft_unset_help_3(tmp, list);
			break ;
		}
		else if (!check)
			ft_unset_help1(shell, str, j);
		else if (tmp->next)
			ft_unset_help_2(tmp, str, j, count);
	}
	return (0);
}

void			ft_command_unset(t_shell *shell)
{
	shell->j++;
	ft_exitstatus(shell, 0);
	ft_unset(shell, &shell->list_arg->arg[shell->j], &shell->lst_before_export);
	ft_unset(shell, &shell->list_arg->arg[shell->j], &shell->list_env);
}
