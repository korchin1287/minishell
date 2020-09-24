/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_bash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 18:18:12 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/24 13:11:12 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_command_bash(t_shell *shell)
{
	char **str_path;
	DIR *dir;
	struct dirent *entry;
	int	flag2;
	char **env;
	int k;

	env = make_str(&shell->list_env, ft_lstsize(shell->list_env));
	flag2 = 0;
	k = 0;
	while(env[k])
	{
		if (ft_strncmp(env[k], "PATH=", 5) == 0)
		{
			str_path = ft_split(&env[k][5], ':');
			break;
		}
		k++;
	}
	k = 0;
	while (str_path[k])
	{
		dir = opendir(str_path[k]);
		if (!dir)
		{
			perror("diropen");
			exit(1);
		}
		
		while ((entry = readdir(dir)) != NULL)
		{
			if ((ft_strcmp(shell->list_arg->arg[shell->j], entry->d_name)) == 0)
			{
				if (shell->list_arg->flag_pipe == 1)
					ft_execve(shell, str_path[k], env);
				else
					shell->flag_exit = ft_pork(shell, str_path[k], env);
				flag2 = 1;
				break ;
			}
		}
		closedir(dir);
		k++;
	}
	if (flag2 == 0)
	{
		if (shell->list_arg->flag_pipe == 1)
			ft_execve(shell, ".", env);
		else
			shell->flag_exit = ft_pork(shell, ".", env);
		if (shell->flag_exit == 127)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(shell->list_arg->arg[shell->j], 2);
			ft_putendl_fd(": command not found", 2);
		}
	}
}