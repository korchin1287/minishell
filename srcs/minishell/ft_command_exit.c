/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:33:15 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/01 14:44:05 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	exit(shell->flag_exit);
}
