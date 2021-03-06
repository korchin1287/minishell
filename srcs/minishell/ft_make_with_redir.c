#include "../minishell.h"

int			ft_make_with_redir_help(t_shell *shell, t_list_arg **tmp)
{
	shell->count = shell->count;
	(*tmp) = *tmp == NULL ? shell->list_arg : *tmp;
	ft_open_file_redir(shell, tmp);
	if (shell->fd_file == -1)
	{
		while (shell->count-- > 0)
			shell->list_arg = shell->list_arg->next;
		return (0);
	}
	if ((*tmp)->flag_pipe == 1)
		pipe(shell->fd);
	return (1);
}

int			ft_make_with_redir_help2(t_shell *shell)
{
	shell->flag_command_bash_not = 1;
	if (shell->list_arg->arg2[shell->j][0])
		command_minishell(shell);
	while (shell->count-- > 0)
		shell->list_arg = shell->list_arg->next;
	return (shell->flag_exit);
}

void		ft_pid_help_this(t_shell *shell, t_list_arg **tmp)
{
	if ((*tmp)->flag_pipe == 1)
	{
		ft_pid_help_open(shell);
		write(1, "\0", 0);
	}
	dup2(shell->fd_file, 1);
	command_minishell(shell);
	close(shell->fd_file);
	exit(shell->flag_exit);
}

void		ft_pid_close_help_this(t_shell *shell, t_list_arg **tmp)
{
	while (shell->count-- > 0)
		shell->list_arg = shell->list_arg->next;
	if ((*tmp)->flag_pipe == 1)
		ft_pid_help_close(shell);
}

int			ft_make_with_redir(t_shell *shell)
{
	pid_t		pid;
	pid_t		wpid;
	int			status;

	if ((ft_make_with_redir_help(shell, &shell->tmp_redir)) == 0)
		return (1);
	if ((ft_make_with_redir_help3(shell)) > -1)
	{
		if (shell->tmp_redir->flag_redir_one_left)
			return (ft_make_with_redir_flag(shell));
		pid = fork();
	}
	else
		return (ft_make_with_redir_help2(shell));
	g_process = pid;
	if (pid == 0)
		ft_pid_help_this(shell, &shell->tmp_redir);
	else if (pid < 0)
		ft_putendl_fd(strerror(errno), 2);
	else
	{
		ft_pid_close_help_this(shell, &shell->tmp_redir);
		wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (WEXITSTATUS(status));
}
