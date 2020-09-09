/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 15:46:34 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/09 15:07:49 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void ft_echo(t_minshl *shell, char *str, int flag)
{
	write(1, str, ft_strlen(str));
	if (flag)
		write(1, " ", 1);
	if (shell->echo_flag == 0 && !flag)
		write (1, "\n", 1);
	if (shell->echo_flag == 1 && !flag)
		write(1, "%\n", 2);
}
void ft_pwd(t_minshl *shell)
{
	if (shell->parser.count_arg == 0)
	{
		ft_putstr_fd(getcwd(NULL, 0), 1);
			write(1, "\n", 1);
	}
}

void ft_env(t_minshl *shell)
{
	int k;

	k = 0;
	while(shell->env[k])
	{
		if (shell->cd_flag == 0 && (ft_strncmp(shell->env[k], "OLDPWD=", 7)) == 0)
			k++;
		ft_putendl_fd(shell->env[k], 1);
		k++;
	}
}
void ft_cd(t_minshl *shell, char *str)
{
	shell->cd_flag = 1;
	int k;
	char *tmp = getcwd(NULL, 0);
	if (shell->parser.count_arg == 0)
	{
		while (shell->env[k])
		{
			if (!(ft_strncmp(shell->env[k], "HOME=", 4)))
			{
				str = ft_strdup(&shell->env[k][5]);
				break ;
			}
			k++;
		}
		
	}
	if ((k = chdir(str)) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	else
	{
		while (shell->env[k])
		{
			if (!(ft_strncmp(shell->env[k], "PWD=", 4)))
			{
				shell->env[k] = ft_strjoin("PWD=", getcwd(NULL, 0));
				break ;
			}
			k++;
		}
		k = 0;
		while (shell->env[k])
		{
			if ((ft_strncmp(shell->env[k], "OLDPWD=", 7)) == 0)
				shell->env[k] = ft_strjoin("OLDPWD=", tmp);
			k++;
		}
	}
}


int	main(int argc, char **argv, char **env)
{
	int k;
	int i;
	char *line;
	char **str;
	char *tmp;
	char *old_pwd;
	char *buf[100];
	line = NULL;
	t_minshl shell;
	
	shell.cd_flag = 0;
	shell.env = env;
	write(1, "minishell > ", 12);
	k = 0;
	while (1)
	{
		if ((k = (ft_get_next_line(0, &line)) > 0))
		{	
			str = ft_split(line, ' ');
			ft_parse_line(&shell, line);
			free(line);
			line = NULL;
		}
		// else if (str[0] && str[0][0] == '$' && str[0][1] == '?')
		// {
		// 	ft_putstr_fd("minishell: ", 2);
		// 	ft_putnbr_fd(errno, 2);
		// 	ft_putendl_fd(": command not found", 2);
		// }
		// else if (str[0])
		// {
		// 	ft_putstr_fd("minishell: ", 2);
		// 	ft_putstr_fd(str[0], 2);
		// 	ft_putendl_fd(": command not found", 2);
		// }
		
		write(1, "minishell > ", 12);
	}
	return (0);
}