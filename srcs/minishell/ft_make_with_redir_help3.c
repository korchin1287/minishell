/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_with_redir_help3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 17:14:53 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/04 17:22:03 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_make_with_redir_help3(t_shell *shell)
{
	char	**str;
	int		a;

	str = make_str(&shell->list_env, ft_lstsize(shell->list_env));
	a = ft_command_bash_help(shell, str);
	ft_free_str(&shell->str_path);
	ft_free_str(&str);
	return (a);
}
