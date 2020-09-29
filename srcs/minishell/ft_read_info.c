/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 20:30:10 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/28 15:35:28 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int   ft_read_info(t_shell *shell)
{
	
	int k;
	
	g_line = NULL;
	if ((k = (ft_get_next_line(0, &g_line)) > 0))
		{
			if (!(ft_parse_line(shell, g_line)))
			{
				ft_print_name();
				return (0);
			}
			shell->tmp_arg = shell->list_arg;
			ft_free_null(g_line);
		}
	if (k == 0)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	return (1);
}