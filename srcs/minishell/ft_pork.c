/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:01:56 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/21 19:23:30 by nofloren         ###   ########.fr       */
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

void	ft_is_pipe(int *fd1, int *fd2)
{
	dup2(fd1[1], 1);
}

int		ft_pork(t_shell *shell, char *path, char **env)
{
	pid_t pid;
	pid_t wpid;
	int status;


	int savefd;
	int oldfd;
	if (shell->list_arg->flag_pipe == 1)
		pipe(shell->fd1);
	// if (shell->list_arg->flag_pipe2 == 1)
	// 	pipe(shell->fd2);
	savefd = open("test.txt", O_CREAT | O_RDWR, 0666);
	pid = fork();
	char *s2 = ft_strjoin(path, "/");
	s2 = ft_strjoin(s2, shell->list_arg->arg[shell->j]);
	if (pid == 0)
	{
		if (shell->list_arg->flag_pipe == 1)
		{
			dup2(shell->fd1[1], 1);
			close(shell->fd1[0]);
		}
		if (shell->list_arg->flag_pipe == 0)
		{
			dup2(shell->fd1[0], 0);
			close(shell->fd1[1]);
		}
		// if (shell->list_arg->flag_pipe2 == 1)
		// {
		// 	dup2(shell->fd1[0], 0);
		// 	close(shell->fd1[1]);
		// 	dup2(shell->fd2[1], 1);
		// 	close(shell->fd2[0]);
		// }
		
		
		if (execve(s2, &shell->list_arg->arg[shell->j], env) == -1)
		{

			shell->flag_exit = WEXITSTATUS(status);
			exit (WEXITSTATUS(status));
		}
	}
	else if (pid < 0)
		perror("lsh");
	else
	{
	//	close(shell->fd1[0]);
		close(shell->fd1[1]);
		wpid = waitpid(pid, &status, WUNTRACED);
	}
	
	return (WEXITSTATUS(status));
}
