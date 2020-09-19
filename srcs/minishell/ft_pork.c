/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:01:56 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/19 14:00:45 by ndreadno         ###   ########.fr       */
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

int		ft_pork(char *s, char *path, char **str, char **env)
{
	pid_t pid;
	pid_t wpid;
	int status;

	pid = fork();
	char *s2 = ft_strjoin(path, "/");
	s2 = ft_strjoin(s2, s);
	if (pid == 0)
	{
		if (execve(s2, str, env) == -1)
		{
			flag_exit = WEXITSTATUS(status);
			exit (WEXITSTATUS(status));
		}
	}
	else if (pid < 0)
		perror("lsh");
	else
		wpid = waitpid(pid, &status, WUNTRACED);
	return (WEXITSTATUS(status));
}
