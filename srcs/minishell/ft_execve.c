/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 17:42:47 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/02 20:03:50 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execve(t_shell *shell, char *path, char **env)
{
	int		status;
	char	*s2;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	s2 = ft_strjoin(tmp, shell->list_arg->arg[shell->j]);
	ft_free_null((void **)&tmp);
	if (execve(s2, &shell->list_arg->arg[shell->j], env) == -1)
	{
		ft_exitstatus(shell, WEXITSTATUS(status));
		exit(WEXITSTATUS(status));
	}
	ft_free_null((void **)&s2);
	return (WEXITSTATUS(status));
}
