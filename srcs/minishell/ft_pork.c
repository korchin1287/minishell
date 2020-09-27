/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:01:56 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/26 18:16:24 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_pork(t_shell *shell, char *path, char **env)
{
	pid_t pid;
	pid_t wpid;
	int status;
	char *s2;

	pid = fork();
	process = pid;
	
	s2 = ft_strjoin(ft_strjoin(path, "/"), shell->list_arg->arg[shell->j]);
	if (pid == 0)
	{
		if (execve(s2, &shell->list_arg->arg[shell->j], env) == -1)
		{
		//	shell->flag_exit = WEXITSTATUS(status);
			ft_make_wexitstatus(shell, WEXITSTATUS(status));
			exit (WEXITSTATUS(status));
		}
	}
	else if (pid < 0)
		perror("lsh");
	else
		wpid = waitpid(pid, &status, WUNTRACED);
	free(s2);
	return (WEXITSTATUS(status));
}
