/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:01:56 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/24 13:14:52 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/types.h>
#include <errno.h>
#include <sys/errno.h>
#include <stdio.h>
#include <dirent.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int		ft_pork(t_shell *shell, char *path, char **env)
{
	pid_t pid;
	pid_t wpid;
//	int status;

	pid = fork();
	process = pid;
	char *s2 = ft_strjoin(path, "/");
	s2 = ft_strjoin(s2, shell->list_arg->arg[shell->j]);
	if (pid == 0)
	{
		if (execve(s2, &shell->list_arg->arg[shell->j], env) == -1)
		{
			shell->flag_exit = WEXITSTATUS(shell->status);
			exit (WEXITSTATUS(shell->status));
		}
		// if (shell->list_arg->flag_pipe)
		// 	close(shell->fd1[1]);
		// if (shell->list_arg->flag_pipe == 0 /*&& !shell->list_arg->back*/)
		// {
		// 	close(shell->fd1[0]);
		// }
		// if (shell->list_arg->flag_pipe == 1 && shell->list_arg->back && shell->list_arg->back->flag_pipe == 1)
		// {
		// 	close(shell->fd1[0]);
		// 	//close(shell->fd1[1]);
		// 	close(shell->fd2[1]);
		// 	//close(shell->fd2[0]);
		// }
		
		// if (shell->list_arg->flag_pipe == 0  &&  shell->list_arg->back && shell->list_arg->back->flag_pipe == 1/*&& !shell->list_arg->back*/)
		// {
		// 	close(shell->fd2[0]);
		// }
	}
	else if (pid < 0)
		perror("lsh");
	else
		wpid = waitpid(pid, &shell->status, WUNTRACED);
	return (WEXITSTATUS(shell->status));
}
