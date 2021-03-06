#include "../minishell.h"

static void	ft_command_cd_help3(t_list *tmp2, char **tmp)
{
	while (tmp2)
	{
		if (((ft_strncmp(tmp2->content, "OLDPWD=", 7)) == 0) ||
			(ft_strcmp("OLDPWD", tmp2->content) == 0))
		{
			ft_free_null((void **)&tmp2->content);
			tmp2->content = ft_strjoin("OLDPWD=", (*tmp));
		}
		tmp2 = tmp2->next;
	}
}

void		ft_command_cd_help2(t_shell *shell, char **tmp, int flag_pwd)
{
	t_list	*tmp2;
	char	*tmp3;

	tmp2 = shell->list_env;
	tmp3 = ft_getcwd();
	while (tmp2)
	{
		if (!(ft_strncmp(tmp2->content, "PWD=", 4)))
		{
			ft_free_null((void **)&tmp2->content);
			tmp2->content = ft_strjoin("PWD=", tmp3);
			flag_pwd = 1;
			break ;
		}
		tmp2 = tmp2->next;
	}
	if (flag_pwd == 0)
		ft_lstadd_back(&shell->lst_before_export, ft_lstnew2(ft_strjoin("PWD=",
			tmp3)));
	tmp2 = shell->list_env;
	ft_command_cd_help3(tmp2, tmp);
	ft_free_null((void **)&tmp3);
}

int			ft_command_cd_help1(t_shell *shell, t_list *tmp2, int flag)
{
	tmp2 = shell->list_env;
	if (!shell->list_arg->arg2[shell->j])
	{
		while (tmp2)
		{
			if (!(ft_strncmp(tmp2->content, "HOME=", 5)))
			{
				flag = 1;
				free(shell->list_arg->arg2[shell->j - 1]);
				shell->list_arg->arg2[shell->j - 1] =
					ft_strdup(&tmp2->content[5]);
				shell->j--;
				break ;
			}
			tmp2 = tmp2->next;
		}
		if (!flag)
		{
			write(2, "minishell: cd: HOME not set\n", 29);
			ft_exitstatus(shell, 1);
			return (1);
		}
	}
	ft_command_cd_help4(shell);
	return (0);
}

static void	ft_command_cd_help(t_shell *shell, char **tmp)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(shell->list_arg->arg2[shell->j], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	ft_free_null((void **)&(*tmp));
	ft_exitstatus(shell, 1);
}

void		ft_command_cd(t_shell *shell)
{
	int		k;
	char	*tmp;
	t_list	tmp2;

	k = 0;
	tmp = ft_getcwd();
	shell->j++;
	if ((ft_command_cd_help1(shell, &tmp2, 0) == 1))
		return ;
	if (shell->list_arg->arg2[shell->j] &&
		(k = chdir(shell->list_arg->arg2[shell->j])) == -1)
	{
		ft_command_cd_help(shell, &tmp);
		return ;
	}
	else
	{
		shell->flag_cd = 0;
		ft_command_cd_help2(shell, &tmp, 0);
	}
	ft_free_null((void **)&tmp);
	ft_exitstatus(shell, 0);
}
