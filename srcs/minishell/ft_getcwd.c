/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_getcwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 16:00:54 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/02 16:06:02 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getcwd(void)
{
	char *ptr;

	if ((ptr = getcwd(NULL, 0)) == NULL)
		ft_putendl_fd(strerror(errno), 2);
	return (ptr);
}
