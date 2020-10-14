/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 16:00:54 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/14 17:19:59 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error_name(t_shell *shell)
{
	if (shell->list_arg->arg[shell->j][0] == '\0')
		ft_putstr_fd(shell->list_arg->arg2[shell->j], 2);
	else 
		ft_putstr_fd(shell->list_arg->arg[shell->j], 2);
}

char	*ft_getcwd(void)
{
	char *ptr;

	if ((ptr = getcwd(NULL, 0)) == NULL)
		ft_putendl_fd(strerror(errno), 2);
	return (ptr);
}
