/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_with_redir_help3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 17:14:53 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/15 17:03:34 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_what_command2(t_shell *shell)
{
	if ((ft_strcmp(shell->list_arg->arg2[shell->j], "export")) == 0
		&& shell->list_arg->arg2[shell->j + 1])
		return (1);
	else if ((ft_strcmp(shell->list_arg->arg2[shell->j], "cd")) == 0)
		return (1);
	else if ((ft_strcmp(shell->list_arg->arg2[shell->j], "exit")) == 0)
		return (1);
	else if ((ft_strcmp(shell->list_arg->arg2[shell->j], "unset")) == 0)
		return (1);
	else
		return (0);
}

int			ft_make_with_redir_help3(t_shell *shell)
{
	char	**str;
	int		a;

	str = make_str(&shell->list_env, ft_lstsize(shell->list_env));
	ft_help_this(shell);
	if ((ft_what_command(shell)) == 0)
		a = ft_command_bash_help(shell, str);
	else
	{
		a = 1;
		if (ft_what_command2(shell))
			a = -1;
	}
	ft_free_str(&shell->str_path);
	ft_free_str(&str);
	return (a);
}
