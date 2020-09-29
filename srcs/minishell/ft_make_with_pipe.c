/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_with_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 17:31:44 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/29 11:16:43 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    ft_make_with_pipe(t_shell *shell)
{
	pid_t pid;
	pid_t wpid;
	int status;
	t_list_arg *tmp;
	int fd_file;
	int i;

	i = 0;
	shell->flag_redirect = 1;
	pipe(shell->fd);
	pid = fork();
	process = pid;
	if (pid == 0)
	{
		close (shell->fd[0]);
		dup2(shell->fd[1], 1);
		close(shell->fd[1]);
		command_minishell(shell);
		close(fd_file);
		exit(shell->flag_exit);
	}
	else if (pid < 0)
		perror("lsh");
	else
	{
		close (shell->fd[1]);
		dup2(shell->fd[0], 0);
		close(shell->fd[0]);
		wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (WEXITSTATUS(status));
}