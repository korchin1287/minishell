#include "../minishell.h"

void	ft_command_bash_help1(t_shell *shell, char **env)
{
	char	*path;

	shell->flag_stat = 0;
	path = shell->list_arg->arg[shell->j][0] == '.' ? "./" : "";
	if (shell->flag_command_bash_not == 0 && (shell->list_arg->flag_pipe == 1
		|| shell->list_arg->flag_redir_one == 1 ||
		shell->list_arg->flag_redir_one_left == 1 ||
		shell->list_arg->flag_redir_two == 1))
		shell->flag_exit = ft_execve(shell, path, env);
	else
		shell->flag_exit = ft_pork(shell, path, env);
	ft_exitstatus(shell, shell->flag_exit);
}
