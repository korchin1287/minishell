/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_bash_help1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:26:06 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/01 19:44:15 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_command_bash_help1(t_shell *shell, char **env)
{
	DIR		*dir;
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
	if ((dir = opendir(shell->list_arg->arg[shell->j])))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->list_arg->arg[shell->j], 2);
		ft_putendl_fd(": is a directory", 2);
		ft_exitstatus(shell, 126);
		closedir(dir);
	}
	else if (shell->flag_exit == 127 || shell->flag_stat == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->list_arg->arg[shell->j], 2);
		ft_putendl_fd(": command not found", 2);
	}
}
