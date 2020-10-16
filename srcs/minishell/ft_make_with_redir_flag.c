/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_with_redir_flag.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 16:57:12 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/15 17:13:13 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_make_with_redir_flag(t_shell *shell)
{
	int status;

	status = 0;
	dup2(shell->fd_file, 1);
	status = ft_make_with_left_redir(shell);
	close(shell->fd_file);
	return (status);
}
