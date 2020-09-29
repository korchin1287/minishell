/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_with_left_redir.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:35:30 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/29 15:34:14 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    ft_make_with_left_redir(t_shell *shell)
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
	fd_file = -1;
	while (tmp->flag_redir_one_left == 1)
	{
		ft_parse_list(tmp->next, shell->lst_before_export, shell->list_env);
		if ((fd_file = open(tmp->next->arg[0], O_RDWR, 0666)) < 0)
			break;
		i++;
		if (tmp->next->arg[1])
		{
			ft_lstadd_back3(&shell->costl, ft_lstnew3(&tmp->next->arg[1]));
		}
		tmp = tmp->next;
	}
	if (fd_file == -1)
	{
		while (shell->list_arg->next && shell->list_arg->flag_end != 1)
			shell->list_arg = shell->list_arg->next;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tmp->next->arg[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		ft_exitstatus(shell, 1);
		return (0);
	}
	if (tmp->flag_pipe == 1)
	{
		pipe(shell->fd);
	}
	pid = fork();
	process = pid;
	if (pid == 0)
	{
		if (shell->list_arg->flag_redir_one_left == 1)
			dup2(fd_file, 0);
		if (tmp->flag_pipe == 1)
		{
			close (shell->fd[0]);
			dup2(shell->fd[1], 1);
			close(shell->fd[1]);
		}
		command_minishell(shell);
		close(fd_file);
		exit(0);
	}
	else if (pid < 0)
		perror("lsh");
	else
	{
		while (i-- > 0)
			shell->list_arg = shell->list_arg->next;
		if (tmp->flag_pipe == 1)
		{
			close (shell->fd[1]);
			dup2(shell->fd[0], 0);
			close(shell->fd[0]);
		}
		wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (WEXITSTATUS(status));
}