/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 16:24:20 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/03 18:41:16 by ndreadno         ###   ########.fr       */
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