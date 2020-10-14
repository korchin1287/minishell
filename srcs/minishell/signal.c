/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 21:49:33 by ndreadno          #+#    #+#             */
/*   Updated: 2020/10/14 18:19:47 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_sigint(int signal)
{
	signal = 0;
	if (g_line && ft_strlen(g_line))
	{
		ft_free_null((void **)&g_line);
		g_line = ft_malloc(sizeof(char), 1);
		g_line[0] = '\0';
		g_buf[0] = '\0';
	}
	g_status = 1;
	write(1, "\b\b  \b\b", 6);
	write(1, "\n", 1);
	ft_print_name();
	g_process = 0;
}

static void	ft_sigquit(int signal)
{
	signal = 0;
	write(1, "\b\b  \b\b", 6);
}

void		ft_singnal(void)
{
	signal(SIGINT, &ft_sigint);
	signal(SIGQUIT, &ft_sigquit);
}
