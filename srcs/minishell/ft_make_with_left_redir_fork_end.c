#include "../minishell.h"

int		ft_make_with_left_redir_fork_end(t_shell *shell, t_list_arg **tmp)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	g_process = pid;
	if (pid == 0)
		ft_pid_help_redir_left(shell, tmp);
	else if (pid < 0)
		ft_putendl_fd(strerror(errno), 2);
	else
	{
		while (shell->count-- > 0)
			shell->list_arg = shell->list_arg->next;
		if ((*tmp)->flag_pipe == 1)
			ft_pid_help_close(shell);
		wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (WEXITSTATUS(status));
}
