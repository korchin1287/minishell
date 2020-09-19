/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 17:05:52 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/18 17:51:24 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_command_cd(t_shell *shell)
{
	int k = 0;
	char *tmp = getcwd(NULL, 0);
	shell->j++;
	t_list *tmp2;
	tmp2 = shell->list_env;
	if (!shell->list_arg->arg[shell->j])
	{
		while (tmp2)
		{
			if (!(ft_strncmp(tmp2->content, "HOME=", 4)))
			{
				free(shell->list_arg->arg[shell->j - 1]);
				shell->list_arg->arg[shell->j - 1] = ft_strdup(&tmp2->content[5]);
				shell->j--;
				break ;
			}
			tmp2 = tmp2->next;
		}
	}
	if (shell->list_arg->arg[shell->j] && (k = chdir(shell->list_arg->arg[shell->j])) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(shell->list_arg->arg[shell->j], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		shell->flag_exit = 1;
	}
	else
	{
		k = 0;
		shell->flag_cd = 0;
		tmp2 = shell->list_env;
		while (tmp2)
		{
			if (!(ft_strncmp(tmp2->content, "PWD=", 4)))
			{
				tmp2->content = ft_strjoin("PWD=", getcwd(NULL, 0));
				break ;
			}
			tmp2 = tmp2->next;
		}
		k = 0;
		tmp2 = shell->list_env;
		while (tmp2)
		{
			if ((ft_strncmp(tmp2->content, "OLDPWD=", 7)) == 0)
				tmp2->content = ft_strjoin("OLDPWD=", tmp);
			tmp2 = tmp2->next;
		}
	}
}