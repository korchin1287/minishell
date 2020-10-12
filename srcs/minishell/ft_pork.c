/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:01:56 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/12 12:43:30 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_check_stat_help(t_shell *shell, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->list_arg->arg[shell->j], 2);
		ft_putendl_fd(": is a directory", 2);
	}
	else if (i == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->list_arg->arg[shell->j], 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	else if (i == 3)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->list_arg->arg[shell->j], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->list_arg->arg[shell->j], 2);
		ft_putendl_fd(": command not found", 2);
	}
}

int			ft_check_stat(t_shell *shell, char **s2)
{
	struct stat	buf;
	int			result;

	result = stat((*s2), &buf);
	if (result == 0)
	{
		if ((buf.st_mode & S_IFDIR))
		{
			ft_check_stat_help(shell, 1);
			return (126);
		}
		else if ((buf.st_mode & S_IXUSR) == 0)
		{
			ft_check_stat_help(shell, 2);
			return (126);
		}
		return (0);
	}
	else if (ft_strchr(shell->list_arg->arg[shell->j], '/'))
		ft_check_stat_help(shell, 3);
	else
		ft_check_stat_help(shell, 4);
	ft_exitstatus(shell, 127);
	return (127);
}

char		*ft_pork_help_1(char *path, t_shell *shell)
{
	char	*tmp;
	char	*s2;

	tmp = ft_strjoin(path, "/");
	s2 = ft_strjoin(tmp, shell->list_arg->arg2[shell->j]);
	ft_free_null((void **)&tmp);
	return (s2);
}

int			ft_pork_help_2(t_shell *shell, char *s2, char **env)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	g_process = pid;
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if ((status = execve(s2, &shell->list_arg->arg2[shell->j], env)) == -1)
			exit(WEXITSTATUS(status));
	}
	else if (pid < 0)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(-1);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (status_return(status));
}

int			ft_pork(t_shell *shell, char *path, char **env)
{
	int		status;
	char	*s2;

	s2 = ft_pork_help_1(path, shell);
	if ((status = ft_check_stat(shell, &s2)))
	{
		ft_free_null((void **)&s2);
		return (status);
	}
	status = ft_pork_help_2(shell, s2, env);
	ft_free_null((void **)&s2);
	return (status);
}
