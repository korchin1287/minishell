#include "../minishell.h"

void	ft_command_env(t_shell *shell)
{
	t_list	*tmp;

	if (!shell->list_arg->arg[shell->j + 1])
	{
		tmp = shell->list_env;
		while (tmp)
		{
			if (!ft_strchr(tmp->content, '='))
			{
				tmp = tmp->next;
				continue;
			}
			if (tmp && shell->flag_cd == 1 &&
				(ft_strncmp(tmp->content, "OLDPWD=", 7)) == 0)
			{
				tmp = tmp->next;
				continue;
			}
			ft_putendl_fd(tmp->content, 1);
			tmp = tmp->next;
		}
		ft_exitstatus(shell, 0);
	}
}
