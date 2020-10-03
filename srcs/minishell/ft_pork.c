/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:01:56 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/03 16:02:27 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_stat(t_shell *shell, char **s2)
{
	struct stat	buf;
	int	result;

	result = stat((*s2), &buf);
	if (result == 0)
	{
		if ((((buf.st_mode & S_IXUSR) == 0) || (buf.st_mode & S_IFDIR)) && shell->flag_stat)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(shell->list_arg->arg[shell->j], 2);
			ft_putendl_fd(": command not found", 2);
			return (127);
		}
	}
	return (0);
}

int			ft_pork(t_shell *shell, char *path, char **env)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	char	*s2;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	s2 = ft_strjoin(tmp, shell->list_arg->arg[shell->j]);
	ft_free_null((void **)&tmp);
	if (ft_check_stat(shell, &s2))
		return (127);
	pid = fork();
	g_process = pid;
	if (pid == 0)
	{
		if ((status = execve(s2, &shell->list_arg->arg[shell->j], env)) == -1)
			exit(WEXITSTATUS(status));
	}
	else if (pid < 0)
		ft_putendl_fd(strerror(errno), 2);
	else
		wpid = waitpid(pid, &status, WUNTRACED);
	ft_free_null((void **)&s2);
	return (WEXITSTATUS(status));
}
