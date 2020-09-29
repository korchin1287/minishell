/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_with_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:33:06 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/29 16:10:32 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_make_first_argv(t_shell *shell)
{
	int count;
	char **str;
	int i;
	int k;
	t_costl *tmp;

	count = ft_cout_mas(shell->list_arg->arg);
	tmp = shell->costl;
	while (tmp)
	{
		count += ft_cout_mas(tmp->content);
		tmp = tmp->next;
	}
	if (!(str = malloc(sizeof(char *) * (count + 1))))
		exit(-1);
	i = 0;
	k = 0;
	while (shell->list_arg->arg[i])
	{
		str[i] = ft_strdup(shell->list_arg->arg[i]);
		i++;
	}
	tmp = shell->costl;
	while (tmp)
	{
		k = -1;
		while (tmp->content[++k])
			str[i++] = ft_strdup(tmp->content[k]);
		tmp = tmp->next;
	}
	str[i] = NULL;
	free(shell->list_arg->arg);
	shell->list_arg->arg = str;
}

// int    ft_make_with_pipe(t_shell *shell, int fd_file)
// {
// 	pid_t pid;
// 	pid_t wpid;
// 	int status;
// 	t_list_arg *tmp;
// 	int fd_file;
// 	int i;

// 	i = 0;
// 	shell->flag_redirect = 1;
// 	pipe(shell->fd);
// 	pid = fork();
// 	process = pid;
// 	if (pid == 0)
// 	{
// 		close (shell->fd[0]);
// 		dup2(shell->fd[1], 1);
// 		close(shell->fd[1]);
// 		command_minishell(shell);
// 		close(fd_file);
// 		exit(shell->flag_exit);
// 	}
// 	else if (pid < 0)
// 		perror("lsh");
// 	else
// 	{
// 		close (shell->fd[1]);
// 		dup2(shell->fd[0], 0);
// 		close(shell->fd[0]);
// 		wpid = waitpid(pid, &status, WUNTRACED);
// 	}
// 	return (WEXITSTATUS(status));
// }

int    ft_make_with_redir(t_shell *shell)
{
    pid_t pid;
	pid_t wpid;
	int status;
	int k;
	t_list_arg *tmp;
	int fd_file;
	int i;

	i = 0;
	shell->flag_redirect = 1;
	tmp = shell->list_arg;
	fd_file = -1;
	while (tmp->flag_redir_one == 1 || tmp->flag_redir_two == 1)
	{
		ft_parse_list(tmp->next, shell->lst_before_export, shell->list_env);
		if (tmp->flag_redir_one == 1)
			fd_file = open(tmp->next->arg[0], O_CREAT | O_RDWR | O_TRUNC, 0666);
		else if (tmp->flag_redir_two == 1)
			fd_file = open(tmp->next->arg[0], O_CREAT | O_RDWR| O_APPEND, 0666);
		if (fd_file == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(tmp->next->arg[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
			ft_exitstatus(shell, 1);
		}
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
		//return (0);
    }
	if (tmp->flag_pipe == 1)
	{
		pipe(shell->fd);
	}
    if ((k = ft_command_bash_help(shell, make_str(&shell->list_env, ft_lstsize(shell->list_env)))) > -1)
		pid = fork();
	else
	{
		shell->flag_command_bash_not = 1;
		ft_command_bash(shell);
		while (i-- > 0)
			shell->list_arg = shell->list_arg->next;
		return (shell->flag_exit);
	}
	
	if (shell->costl)
		ft_make_first_argv(shell);
	process = pid;
	if (pid == 0)
	{
		if (tmp->flag_pipe == 1)
		{
			close (shell->fd[0]);
			dup2(shell->fd[1], 1);
			close(shell->fd[1]);
			write (1, "\0", 0);
		}
		dup2(fd_file, 1);
		command_minishell(shell);
		close(fd_file);
		exit(shell->flag_exit);
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