#include "../minishell.h"

void	ft_get_path(t_shell *shell, char **env)
{
	int	k;

	k = 0;
	while (env[k])
	{
		if (ft_strncmp(env[k], "PATH=", 5) == 0)
		{
			shell->str_path = ft_split(&env[k][5], ':');
			break ;
		}
		k++;
	}
}

int		ft_command_bash_help(t_shell *shell, char **env)
{
	DIR				*dir;
	struct dirent	*entry;
	int				k;

	k = 0;
	ft_get_path(shell, env);
	while (shell->str_path && shell->str_path[k])
	{
		dir = opendir(shell->str_path[k]);
		while (dir && (entry = readdir(dir)) != NULL)
		{
			if ((ft_strcmp(shell->list_arg->arg2[shell->j], entry->d_name)) == 0
				|| (ft_strcmp(shell->list_arg->arg2[shell->j], entry->d_name))
				== 0)
			{
				closedir(dir);
				return (k);
			}
		}
		if (dir)
			closedir(dir);
		k++;
	}
	return (-1);
}

void	ft_command_bash(t_shell *shell)
{
	char	**env;
	int		k;

	env = make_str(&shell->list_env, ft_lstsize(shell->list_env));
	shell->flag_command_bash = 0;
	if ((k = ft_command_bash_help(shell, env)) > -1)
	{
		shell->flag_stat = 1;
		if (shell->flag_command_bash_not == 0 &&
			(shell->list_arg->flag_pipe == 1 ||
			shell->list_arg->flag_redir_one == 1 ||
			shell->list_arg->flag_redir_one_left == 1 ||
			shell->list_arg->flag_redir_two == 1))
			shell->flag_exit = ft_execve(shell, shell->str_path[k], env);
		else
			shell->flag_exit = ft_pork(shell, shell->str_path[k], env);
		shell->flag_command_bash = 1;
	}
	if (shell->flag_command_bash == 0)
		ft_command_bash_help1(shell, env);
	ft_exitstatus(shell, shell->flag_exit);
	ft_free_str(&env);
	ft_free_str(&shell->str_path);
}
