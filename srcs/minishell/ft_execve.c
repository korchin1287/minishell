#include "../minishell.h"

int	ft_execve(t_shell *shell, char *path, char **env)
{
	int		status;
	char	*s2;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	s2 = ft_strjoin(tmp, shell->list_arg->arg2[shell->j]);
	ft_free_null((void **)&tmp);
	if ((status = ft_check_stat(shell, &s2)))
	{
		ft_free_null((void **)&s2);
		return (status);
	}
	if ((status = execve(s2, &shell->list_arg->arg2[shell->j], env)) == -1)
	{
		ft_exitstatus(shell, 127);
		exit(WEXITSTATUS(status));
	}
	ft_free_null((void **)&s2);
	return (WEXITSTATUS(status));
}
