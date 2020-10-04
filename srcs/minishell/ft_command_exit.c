/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:33:15 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/04 16:40:58 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_clear_list2(t_list **head)
{
	t_list *tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		ft_free_null((void **)&tmp->content);
		tmp->content = NULL;
		ft_free_null((void **)&tmp);
		tmp = NULL;
	}
}

static void	ft_exit_free(t_shell *shell)
{
	ft_clear_list2(&shell->list_env);
	ft_clear_list2(&shell->lst_before_export);
}

static void	ft_exit_help(t_shell *shell)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(shell->list_arg->arg[shell->j + 1], 2);
	ft_putendl_fd(": numeric argument required", 2);
	exit(255);
}

void		ft_exit(t_shell *shell)
{
	int i;

	ft_putendl_fd("exit", 2);
	if (shell->list_arg->arg[shell->j + 1])
	{
		i = 0;
		while (shell->list_arg->arg[shell->j + 1][i] != '\0')
		{
			if (!ft_isdigit(shell->list_arg->arg[shell->j + 1][i++]))
				ft_exit_help(shell);
		}
		ft_exitstatus(shell, ft_atoi(shell->list_arg->arg[shell->j + 1]));
	}
	if (shell->list_arg->arg[shell->j + 1] &&
		shell->list_arg->arg[shell->j + 2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		ft_exitstatus(shell, 1);
		return ;
	}
	ft_exit_free(shell);
	exit(shell->flag_exit);
}
