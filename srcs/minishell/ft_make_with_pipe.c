/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_with_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 17:31:44 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/24 21:05:25 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	tmp = shell->list_arg;
	while (tmp->flag_redir_one == 1 || tmp->flag_redir_two == 1)
	{
		if (tmp->flag_redir_one == 1)
   			fd_file = open(tmp->next->arg[0], O_CREAT | O_RDWR | O_TRUNC, 0666);
		else if (tmp->flag_redir_two == 1)
			fd_file = open(tmp->next->arg[0], O_CREAT | O_RDWR| O_APPEND, 0666);
		i++;
		tmp = tmp->next;
	}
	if (shell->list_arg->flag_pipe == 1)
		pipe(shell->fd);
	pid = fork();
	process = pid;
	if (pid == 0)
	{
		if (shell->list_arg->flag_redir_one == 1 || shell->list_arg->flag_redir_two == 1)
			dup2(fd_file, 1);
		else
		{
			close (shell->fd[0]);
			dup2(shell->fd[1], 1);
			close(shell->fd[1]);
		}
		command_minishell(shell);
		exit(0);
	}
	else if (pid < 0)
		perror("lsh");
	else
	{
		while (i > 0)
		{
			i--;
			shell->list_arg = shell->list_arg->next;
		}
		if (shell->list_arg->flag_pipe == 1)
		{
			close (shell->fd[1]);
			dup2(shell->fd[0], 0);
			close(shell->fd[0]);
		}
		wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (WEXITSTATUS(status));
}