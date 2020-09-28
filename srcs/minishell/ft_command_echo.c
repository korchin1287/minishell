/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 17:58:13 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/27 20:07:54 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_command_echo(t_shell *shell)
{
    int flag_n;

    shell->j++;
    if (shell->list_arg->arg[shell->j])
    {
        flag_n = 0;
        if (shell->list_arg->arg[shell->j] && (ft_strcmp(shell->list_arg->arg[shell->j], "-n") == 0))
        {
            flag_n = 1;
            shell->j++;
        }
        while (shell->list_arg->arg[shell->j])
        {
            if (shell->list_arg->arg[shell->j])
            {
                write(1, shell->list_arg->arg[shell->j], ft_strlen(shell->list_arg->arg[shell->j]));
                if (shell->list_arg->arg[shell->j + 1])
                    write(1, " ", 1);
            }
            shell->j++;
        }
        if (flag_n == 0)
            write(1, "\n", 1);
    }
    else
        write (1, "\n", 1);
    ft_exitstatus(shell, 0);
}