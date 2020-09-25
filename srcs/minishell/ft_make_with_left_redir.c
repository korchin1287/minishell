/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_with_left_redir.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:35:30 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/25 20:20:27 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (tmp->flag_redir_one_left == 1)
	{
		ft_parse_list(tmp->next, shell->lst_before_export, shell->list_env);
		fd_file = open(tmp->next->arg[0], O_RDWR, 0666);
		i++;
		if (tmp->next->arg[1])
		{
			ft_lstadd_back3(&shell->costl, ft_lstnew3(&tmp->next->arg[1]));
		}
		tmp = tmp->next;
	}
	if (fd_file == -1 && (tmp->flag_redir_one == 1 || tmp->flag_redir_two == 1))
    {
        shell->flag_exit = 1;
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
		while (i > 0)
		{
			i--;
			shell->list_arg = shell->list_arg->next;
		}
		wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (WEXITSTATUS(status));
}