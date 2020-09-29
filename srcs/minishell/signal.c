/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 21:49:33 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/28 15:28:19 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_sigint(int signal)
{
	if (process != 0)
		kill(process, signal);
	if (process == 0)
	{
		if (g_line && ft_strlen(g_line))
		{
			ft_free_null(g_line);
			g_line = ft_malloc(sizeof(char), 1);
			g_line[0] = '\0';
		}
		write(1, "\n", 1);
		ft_print_name();
	}
	process = 0;
}

void ft_sigquit(int signal)
{
	if (process != 0)
	{
		kill(process, signal);
		write(1, "Quit: 3\n", 8);
		ft_print_name();
	}
	// if (process == 0)
	// {
	// 	write(1, "\n", 1);
	// 	ft_print_name();
	// }
	process = 0;
}
void ft_singnal(t_shell *shell)
{
	signal(SIGINT, &ft_sigint);
	signal(SIGQUIT, &ft_sigquit);
}