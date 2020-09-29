/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 17:42:47 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/29 11:09:42 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_execve(t_shell *shell, char *path, char **env)
{
	int status;
	char *s2 = ft_strjoin(path, "/");
	s2 = ft_strjoin(s2, shell->list_arg->arg[shell->j]);
    if (execve(s2, &shell->list_arg->arg[shell->j], env) == -1)
	{
		ft_exitstatus(shell, WEXITSTATUS(status));
		exit (WEXITSTATUS(status));
	}
	return (WEXITSTATUS(status));
}