/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 15:46:34 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/14 18:45:07 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		command_minishell(t_shell *shell)
{
	if ((shell->list_arg->arg[shell->j][0] == '\0' || (ft_strcmp(shell->list_arg->arg[shell->j], "export")) == 0) 
		&& (ft_strcmp(shell->list_arg->arg2[shell->j], "export")) == 0)
		ft_command_export(shell);
	else if ((shell->list_arg->arg[shell->j][0] == '\0' || (ft_strcmp(shell->list_arg->arg[shell->j], "cd")) == 0)
		&& (ft_strcmp(shell->list_arg->arg2[shell->j], "cd")) == 0)
		ft_command_cd(shell);
	else if ((ft_strcmp(shell->list_arg->arg2[shell->j], "pwd")) == 0)
		ft_command_pwd(shell);
	else if ((ft_strcmp(shell->list_arg->arg2[shell->j], "env")) == 0)
		ft_command_env(shell);
	else if ((ft_strcmp(shell->list_arg->arg2[shell->j], "echo")) == 0)
		ft_command_echo(shell);
	else if ((shell->list_arg->arg[shell->j][0] == '\0' || (ft_strcmp(shell->list_arg->arg[shell->j], "exit")) == 0)
		&& (ft_strcmp(shell->list_arg->arg2[shell->j], "exit")) == 0)
		ft_exit(shell);
	else if ((shell->list_arg->arg[shell->j][0] == '\0' || (ft_strcmp(shell->list_arg->arg[shell->j], "unset")) == 0) 
		&& (ft_strcmp(shell->list_arg->arg2[shell->j], "unset")) == 0)
		ft_command_unset(shell);
	else
		ft_command_bash(shell);		
}

static void	ft_before_while(t_shell *shell, char **env)
{
	g_process = 0;
	g_status = 0;
	ft_shell_init(shell);
	ft_list_create(&shell->list_env, env);
	ft_print_name();
	ft_exitstatus(shell, shell->flag_exit);
	ft_singnal();
}

void		ft_while_help(t_shell *shell)
{
	ft_parse_list_line(shell, &shell->list_arg);
	ft_add_list_before_export(shell);
	if (shell->list_arg->arg[shell->j] || (!shell->list_arg->arg[shell->j]
		&& (shell->list_arg->flag_pipe == 1 ||
		shell->list_arg->flag_redir_one == 1 ||
		shell->list_arg->flag_redir_two == 1)))
	{
		if (shell->list_arg->flag_pipe == 1)
			shell->flag_exit = ft_make_with_pipe(shell);
		else if (shell->list_arg->flag_redir_one == 1 ||
			shell->list_arg->flag_redir_two == 1)
			shell->flag_exit = ft_make_with_redir(shell);
		else if (shell->list_arg->flag_redir_one_left == 1)
			ft_make_with_left_redir(shell);
		else
			command_minishell(shell);
	}
}

static void	ft_end_while(t_shell *shell)
{
	dup2(shell->savestdin, 0);
	dup2(shell->sevestdout, 1);
	ft_print_name();
	ft_free_null((void **)&shell->costl);
	ft_clear_lst(&shell->tmp_arg);
	shell->tmp_redir = NULL;
}

int			main(int argc, char **argv, char **env)
{
	t_shell	shell;

	argc *= 1;
	argv = NULL;
	ft_before_while(&shell, env);
	while (1)
	{
		ft_singnal();
		if (!ft_read_info(&shell))
			continue;
		shell.j = 0;
		ft_main_help(&shell);
		ft_end_while(&shell);
	}
	return (0);
}
