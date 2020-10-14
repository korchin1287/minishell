/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 17:58:13 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/14 12:44:36 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_command_echo_help(t_shell *shell)
{
	write(1, shell->list_arg->arg2[shell->j],
		ft_strlen(shell->list_arg->arg2[shell->j]));
	if (shell->list_arg->arg2[shell->j + 1])
		write(1, " ", 1);
}

void		ft_command_echo(t_shell *shell)
{
	int flag_n;

	shell->j++;
	if (shell->list_arg->arg2[shell->j])
	{
		flag_n = 0;
		while ((shell->list_arg->arg2[shell->j] &&
			(ft_strcmp(shell->list_arg->arg2[shell->j], "-n") == 0)))
		{
			flag_n = 1;
			shell->j++;
		}
		while (shell->list_arg->arg2[shell->j])
		{
			ft_command_echo_help(shell);
			shell->j++;
		}
		if (flag_n == 0)
			write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
	ft_exitstatus(shell, 0);
}
