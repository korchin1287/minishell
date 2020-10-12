/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_with_redir_help3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 17:14:53 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/12 19:32:21 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_make_with_redir_help3(t_shell *shell)
{
	char	**str;
	int		a;

	str = make_str(&shell->list_env, ft_lstsize(shell->list_env));
	if ((ft_what_command(shell)) == 0)
		a = ft_command_bash_help(shell, str);
	else
		a = 1;
	ft_free_str(&shell->str_path);
	ft_free_str(&str);
	ft_help_this(shell);
	return (a);
}
