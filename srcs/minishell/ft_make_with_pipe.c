#include "../minishell.h"

void	ft_pid_help_open(t_shell *shell)
{
	close(shell->fd[0]);
	dup2(shell->fd[1], 1);
	close(shell->fd[1]);
}

void	ft_pid_help_close(t_shell *shell)
{
	close(shell->fd[1]);
	dup2(shell->fd[0], 0);
	close(shell->fd[0]);
}

int		ft_make_with_pipe(t_shell *shell)
{
	int			status;
	pid_t		pid;
	pid_t		wpid;

	shell->flag_redirect = 1;
	pipe(shell->fd);
	pid = fork();
	g_process = pid;
	if (pid == 0)
	{
		ft_pid_help_open(shell);
		command_minishell(shell);
		exit(shell->flag_exit);
	}
	else if (pid < 0)
		ft_putendl_fd(strerror(errno), 2);
	else
	{
		ft_pid_help_close(shell);
		wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (WEXITSTATUS(status));
}
