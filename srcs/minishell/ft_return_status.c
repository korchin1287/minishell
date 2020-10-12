/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 12:39:20 by ndreadno          #+#    #+#             */
/*   Updated: 2020/10/12 13:34:31 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	status_return(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			return (130);
		if (WTERMSIG(status) == 3)
			return (131);
	}
	return (WEXITSTATUS(status));
}
