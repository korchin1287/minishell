#include "../minishell.h"

int			ft_open_file_redir_left_2(t_shell *shell, t_list_arg **tmp)
{
	if ((*tmp)->next->arg[0][0] == '\0')
	{
		pipe(shell->fd);
		ft_pid_help_close(shell);
		return (1);
	}
	while (shell->list_arg->next && shell->list_arg->flag_end != 1 &&
		shell->list_arg->flag_pipe != 1)
		shell->list_arg = shell->list_arg->next;
	if (shell->list_arg->flag_pipe == 1)
	{
		shell->list_arg = shell->list_arg->next;
		ft_make_with_pipe(shell);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((*tmp)->next->arg[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	ft_exitstatus(shell, 1);
	return (0);
}

int			ft_open_file_redir_left(t_shell *shell, t_list_arg **tmp)
{
	shell->count = shell->count;
	shell->flag_redirect = 1;
	(*tmp) = !shell->tmp_redir ? shell->list_arg : shell->tmp_redir;
	shell->fd_file_left = -1;
	while ((*tmp)->flag_redir_one_left == 1)
	{
		ft_parse_list_line(shell, &(*tmp)->next);
		if ((shell->fd_file_left = open((*tmp)->next->arg[0], O_RDWR, 0666))
			< 0)
			break ;
		shell->count++;
		if ((*tmp)->next->arg[1])
			ft_lstadd_back3(&shell->costl,
				ft_lstnew3(&((*tmp)->next->arg[1])));
		(*tmp) = (*tmp)->next;
	}
	if (shell->fd_file_left == -1)
		return (ft_open_file_redir_left_2(shell, tmp));
	return (1);
}

int			ft_help_costl_redir_left(t_shell *shell, t_list_arg **tmp)
{
	int	status;

	dup2(shell->fd_file_left, 0);
	shell->tmp_redir = *tmp;
	status = ft_make_with_redir(shell);
	close(shell->fd_file);
	return (status);
}

void		ft_pid_help_redir_left(t_shell *shell, t_list_arg **tmp)
{
	dup2(shell->fd_file_left, 0);
	if ((*tmp)->flag_pipe == 1)
		ft_pid_help_open(shell);
	command_minishell(shell);
	close(shell->fd_file_left);
	exit(0);
}

int			ft_make_with_left_redir(t_shell *shell)
{
	if ((ft_open_file_redir_left(shell, &shell->tmp_redir)) == 0)
		return (0);
	if (shell->tmp_redir->flag_pipe == 1)
		pipe(shell->fd);
	if (shell->tmp_redir->flag_redir_one == 1 ||
		(shell->tmp_redir->flag_redir_two == 1))
		return (ft_help_costl_redir_left(shell, &shell->tmp_redir));
	if (ft_make_with_redir_help3(shell) > -1)
		return (ft_make_with_left_redir_fork_end(shell, &shell->tmp_redir));
	return (ft_make_with_redir_help2(shell));
}
