/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 15:46:34 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/07 20:31:33 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <sys/types.h>
#include <errno.h>
#include <sys/errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

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
	int	flag;
	
	flag = 0;
	write(1, "minishell > ", 12);
	k = 0;
	while (1)
	{
		if ((k = (get_next_line(&line)) > 0))
		{	
			str = ft_split(line, ' ');
			free(line);
			line = NULL;
		}
		if (str[0] && ((str[0][0] == 'c') && (str[0][1] == 'd')))
		{
			flag = 1;
			tmp = getcwd(NULL, 0);
			if ((k = chdir(str[1])) == -1)
			{
				ft_putstr_fd("minishell: cd: ", 2);
				ft_putstr_fd(str[1], 2);
				ft_putstr_fd(": ", 2);
				ft_putendl_fd(strerror(errno), 2);
			}
			else
			{
				while (env[k])
				{
					if (!(ft_strncmp(env[k], "PWD=", 4)))
					{
						env[k] = ft_strjoin("PWD=", getcwd(NULL, 0));
						break ;
					}
					k++;
				}
				k = 0;
				while (env[k])
				{
					if ((ft_strncmp(env[k], "OLDPWD=", 7)) == 0)
						env[k] = ft_strjoin("OLDPWD=", tmp);
					k++;
				}
			}
		}
		else if (str[0] && ((str[0][0] == 'p') && (str[0][1] == 'w' && str[0][2] == 'd')))
		{
			ft_putstr_fd(getcwd(NULL, 0), 1);
			write(1, "\n", 1);
		}
		else if (str[0] && ((ft_strncmp(str[0], "env", 3)) == 0))
		{
			k = 0;
			while(env[k])
			{
				if (flag == 0 && (ft_strncmp(env[k], "OLDPWD=", 7)) == 0)
					k++;
				ft_putendl_fd(env[k], 1);
				k++;
			}
		}
		else if (str[0] && ((ft_strncmp(str[0], "echo", 4)) == 0))
		{
			i = 1;
			if (str[1] && ft_strncmp(str[1], "-n", 2))
			{
				while(str[i])
				{
					write(1, str[i], ft_strlen(str[i]));
					if (str[i + 1])
						write(1, " ", 1);
					i++;
				}
				write(1, "\n", 1);
				i++;
			}
			else if (str[1])
			{
				i = 2;
				while(str[i])
				{
					write(1, str[i], ft_strlen(str[i]));
					if (str[i + 1])
						write(1, " ", 1);
					i++;
				}
			}
			else
				write (1, "\n", 1);
		}
		else if (str[0] && str[0][0] == '$' && str[0][1] == '?')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putnbr_fd(errno, 2);
			ft_putendl_fd(": command not found", 2);
		}
		else if (str[0])
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(str[0], 2);
			ft_putendl_fd(": command not found", 2);
		}
		
		write(1, "minishell > ", 12);
	}
	return (0);
}