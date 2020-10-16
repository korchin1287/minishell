/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_list_before_export.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 17:26:44 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/15 17:04:21 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			ft_list_clear_before(t_list **list_before_export)
{
	t_list	*tmp;

	while (*list_before_export)
	{
		tmp = *list_before_export;
		*list_before_export = (*list_before_export)->next;
		ft_free_null((void **)&tmp->content);
		ft_free_null((void **)&tmp);
		tmp = NULL;
	}
}

static int		ft_check_args_be(t_shell *shell)
{
	char	**tmp;
	int		i;
	int		j;

	j = shell->j;
	tmp = shell->list_arg->arg;
	while (tmp[j])
	{
		i = 0;
		while (tmp[j][i] != '\0')
		{
			if (tmp[j][i] == '=')
				break ;
			if (tmp[j][i] != '=' && tmp[j][i + 1] == '\0')
				return (++j);
			i++;
		}
		j++;
	}
	return (0);
}

void			ft_add_list_before_export_help(t_shell *shell, int x)
{
	if (x == 0 && shell->list_arg->flag_disable_char != 0)
		shell->j = shell->list_arg->flag_disable_char - 1;
	else if (x != 0)
		shell->j = --x;
}

static void		ft_help_a_l_b_e(t_shell *shell, char **tmp)
{
	if (!ft_check_list_for_export(&shell->list_env, tmp[shell->j]))
		ft_lstadd_back(&shell->lst_before_export, ft_lstnew2(tmp[shell->j]));
}

void			ft_add_list_before_export(t_shell *shell)
{
	char	**tmp;
	int		i;
	int		x;

	x = ft_check_args_be(shell);
	if (shell->list_arg->arg[0][0] && !x &&
		!(shell->list_arg->flag_disable_char))
	{
		tmp = shell->list_arg->arg;
		while (tmp[shell->j])
		{
			i = -1;
			while (tmp[shell->j][++i] != '\0')
			{
				if (tmp[shell->j][i] == '=' &&
					shell->list_arg->flag_disable_char == 0)
				{
					ft_help_a_l_b_e(shell, tmp);
					break ;
				}
			}
			shell->j++;
		}
	}
	ft_add_list_before_export_help(shell, x);
}
