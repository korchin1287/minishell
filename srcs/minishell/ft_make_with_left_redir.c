/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_with_left_redir.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:35:30 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/29 12:07:21 by ndreadno         ###   ########.fr       */
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
		ft_parse_list_line(shell, tmp->next);
		fd_file = open(tmp->next->arg[0], O_RDWR, 0666);
		i++;
		if (tmp->next->arg[1])
		{
			ft_lstadd_back3(&shell->costl, ft_lstnew3(&tmp->next->arg[1]));
		}
		tmp = tmp->next;
	}
	if (fd_file == -1)
	{
		while (i-- > 0)
			shell->list_arg = shell->list_arg->next;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tmp->arg[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		ft_exitstatus(shell, 1);
		return (0);
	}
	pid = fork();
	process = pid;
	if (pid == 0)
	{
		if (shell->list_arg->flag_redir_one_left == 1)
			dup2(fd_file, 0);
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
		wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (WEXITSTATUS(status));
}