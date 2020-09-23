/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 20:30:10 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/22 20:45:28 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int   ft_read_info(t_shell *shell)
{
	char *line;
	int k;
	
	line = NULL;
	if ((k = (ft_get_next_line(0, &line)) > 0))
		{
			if (!(ft_parse_line(shell->lst_before_export, shell->list_env, &shell->list_arg, line)))
			{
				ft_print_name();
				return (0);
			}
			shell->tmp_arg = shell->list_arg;
			free(line);
			line = NULL;
		}
	if (k == 0)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	return (1);
}