/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 16:24:20 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/03 20:38:01 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_str(char ***str)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!(*str))
		return ;
	while ((*str)[i])
	{
		tmp = (*str)[i];
		i++;
		free(tmp);
		tmp = NULL;
	}
	free(*str);
	*str = NULL;
}