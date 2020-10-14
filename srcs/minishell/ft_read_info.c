/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 20:30:10 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/14 16:39:08 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_command_cd_help4(t_shell *shell)
{
	char	*tmp;

	tmp = shell->list_arg->arg2[shell->j];
	if (shell->list_arg->arg2[shell->j][0] == '\0')
	{
		shell->list_arg->arg2[shell->j] = ft_strjoin(".", "");
		ft_free_null((void **)&tmp);
	}
}

int		ft_read_info(t_shell *shell)
{
	int		k;
	char	*tmp;

	g_line = NULL;
	if ((k = ft_get_next_line(0, &g_line)) > 0)
	{
		if (!(tmp = ft_parse_line(shell, g_line)))
		{
			ft_free_null((void **)&g_line);
			ft_free_null((void **)&tmp);
			ft_print_name(0);
			return (0);
		}
		shell->tmp_arg = shell->list_arg;
		ft_free_null((void **)&g_line);
		ft_free_null((void **)&tmp);
	}
	if (k == 0)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	return (1);
}
