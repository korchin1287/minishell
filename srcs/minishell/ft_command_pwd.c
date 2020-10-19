#include "../minishell.h"

void	ft_command_pwd(t_shell *shell)
{
	char *str;

	str = ft_getcwd();
	ft_putstr_fd(str, 1);
	write(1, "\n", 1);
	ft_free_null((void **)&str);
	ft_exitstatus(shell, 0);
}
