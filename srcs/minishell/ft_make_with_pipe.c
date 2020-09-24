/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_with_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 17:31:44 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/24 16:35:34 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    ft_make_with_pipe(t_shell *shell)
{
	pid_t pid;
	pid_t wpid;
	
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
		if (ft_what_command(shell) != 0)
			exit(0);
	}
	else if (pid < 0)
		perror("lsh");
	else
	{
		close (shell->fd[1]);
		dup2(shell->fd[0], 0);
		close(shell->fd[0]);
		if (ft_what_command(shell) == 0)
			wpid = waitpid(pid, &shell->status, WUNTRACED);
	}
	return (WEXITSTATUS(shell->status));
}