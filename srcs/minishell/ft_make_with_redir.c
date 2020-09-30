/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_with_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:33:06 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/29 20:31:27 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_make_with_redir_help(t_shell *shell, t_list_arg **tmp)
{
	shell->count = 0;
	(*tmp) = shell->list_arg;
	ft_open_file_redir(shell, tmp);
	if (shell->fd_file == -1)
		while (shell->count-- > 0)
			shell->list_arg = shell->list_arg->next;
	if ((*tmp)->flag_pipe == 1)
		pipe(shell->fd);
}

void	ft_make_with_redir_help2(t_shell *shell)
{
	shell->flag_command_bash_not = 1;
	ft_command_bash(shell);
	while (shell->count-- > 0)
		shell->list_arg = shell->list_arg->next;
}

void	ft_pid_help_this(t_shell *shell, t_list_arg **tmp)
{
	if ((*tmp)->flag_pipe == 1)
	{
		ft_pid_help_open(shell);
		write (1, "\0", 0);
	}
	dup2(shell->fd_file, 1);
	command_minishell(shell);
	close(shell->fd_file);
	exit(shell->flag_exit);
}

void	ft_pid_close_help_this(t_shell *shell, t_list_arg **tmp)
{
	while (shell->count-- > 0)
		shell->list_arg = shell->list_arg->next;
	if ((*tmp)->flag_pipe == 1)
		ft_pid_help_close(shell);
}

int    ft_make_with_redir(t_shell *shell)
{
    pid_t pid;
	pid_t wpid;
	t_list_arg *tmp;
	int status;

	ft_make_with_redir_help(shell, &tmp);
    if ((ft_command_bash_help(shell, make_str(&shell->list_env, ft_lstsize(shell->list_env)))) > -1)
		pid = fork();
	else
	{
		ft_make_with_redir_help2(shell);
		return (shell->flag_exit);
	}
	ft_help_this(shell);
	process = pid;
	if (pid == 0)
		ft_pid_help_this(shell, &tmp);
	else if (pid < 0)
		perror("lsh");
	else
	{
		ft_pid_close_help_this(shell, &tmp);
		wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (WEXITSTATUS(status));
}