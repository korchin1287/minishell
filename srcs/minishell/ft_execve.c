/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 17:42:47 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/23 20:03:45 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_execve(t_shell *shell, char *path, char **env)
{
	char *s2 = ft_strjoin(path, "/");
	s2 = ft_strjoin(s2, shell->list_arg->arg[shell->j]);
    if (execve(s2, &shell->list_arg->arg[shell->j], env) == -1)
	{
		shell->flag_exit = WEXITSTATUS(shell->status);
		exit (WEXITSTATUS(shell->status));
	}
}