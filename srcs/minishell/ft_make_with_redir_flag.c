#include "../minishell.h"

int		ft_make_with_redir_flag(t_shell *shell)
{
	int status;

	status = 0;
	dup2(shell->fd_file, 1);
	status = ft_make_with_left_redir(shell);
	close(shell->fd_file);
	return (status);
}
