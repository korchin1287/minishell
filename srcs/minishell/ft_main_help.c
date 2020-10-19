#include "../minishell.h"

void	ft_main_help(t_shell *shell)
{
	while (shell->list_arg)
	{
		ft_while_help(shell);
		if (shell->list_arg->flag_end == 1)
		{
			dup2(shell->savestdin, 0);
			dup2(shell->sevestdout, 1);
			shell->j = 0;
		}
		shell->list_arg = shell->list_arg->next;
		ft_free_null((void **)&shell->costl);
		shell->count = 0;
		shell->tmp_redir = NULL;
	}
}
