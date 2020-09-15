/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 15:46:34 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/11 16:15:29 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <errno.h>
#include <sys/errno.h>
#include <stdio.h>
#include <signal.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

size_t	ft_strlen_2(const char *str, char c)
{
	size_t i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

char *ft_check_doll(char *str, t_list *lst_before_export, t_list *list_env)
{
	int	k;
	t_list *first_dst;
	t_list *first_tmp;

	if (!str)
		return (NULL);
	if (str[0] == '$')
	{
		int count = ft_strlen_2(&str[1], ' ');
		k = 0;
		first_tmp = list_env;
		while (first_tmp)
		{
			if (ft_strncmp(first_tmp->content, &str[1], count) == 0)
				return (&first_tmp->content[count + 1]);
			first_tmp = first_tmp->next;
		}
		first_dst = lst_before_export;
		while (first_dst)
		{
			if (ft_strncmp(first_dst->content, &str[1], count) == 0)
				return (&first_dst->content[count + 1]);
			first_dst = first_dst->next;
		}
	}
	return (NULL);
}

int 	ft_cout_mas(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	ft_swap(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

char 	**ft_sort_mass(char **tmp)
{
	int i;
	int j;
	int len;

	i = 0;
	len = ft_cout_mas(tmp);
	while (i < (len - 1))
	{
		j = 0;
		while (j < (len - i - 1))
		{
			if (ft_strcmp(tmp[j], tmp[j + 1]) > 0)
				ft_swap(&tmp[j], &tmp[j + 1]);
			j++;
		}
		i++;
	}
	return (tmp);
}

t_list	*ft_lstnew2(char *content)
{
	t_list *dst;

	dst = (t_list *)malloc(sizeof(t_list));
	if (dst)
	{
		dst->content = ft_strdup(content);
		dst->next = NULL;
	}
	else
		return (NULL);
	return (dst);
}

void	ft_list_create(t_list **list_env, char **env)
{
	int i;
	char *tmp;
	char *path;

	path = getcwd(NULL, 0);
	path = ft_strjoin(":", path);
	i = 0;
	while(env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			env[i] = ft_strjoin(env[i], path);
		ft_lstadd_back(list_env, ft_lstnew2(env[i]));
		i++;
	}
	free(path);
}

char		**make_str(t_list **list_env, int size)
{
	char	**str;
	int		i;
	t_list	*tmp;

	if (!(str = malloc(sizeof(char *) * (size + 1))))
		exit(-1);
	i = 0;
	tmp = *list_env;
	while (tmp)
	{
		str[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

int	ft_unset(char **str, t_list **list)
{
	t_list *tmp;
	t_list *tmp_2;
	int j;

	j = 0;
	if (!*list)
		return (0);
	while (str[j])
	{
		int count = ft_strlen_2(str[j], ' ');

		tmp = *list;
		if (tmp->next)
		{
			while (tmp->next)
			{
				if (ft_strnstr(tmp->next->content, str[j], count))
				{
					tmp_2 = tmp->next;
					tmp->next = tmp->next->next;
					free(tmp_2->content);
					free(tmp_2);
					tmp_2= NULL;
					break ;
				}
				tmp = tmp->next;
			}
		}
		if (tmp && ft_strnstr(tmp->content, str[j], count))
		{
			free(tmp->content);
			free(tmp);
			*list = NULL;
			break ;
		}
		j++;
	}
	return (0);
}

char	*ft_change_dollar(char *str, t_list *lst_before_export, t_list *list_env)
{
	char *tmp;
	char *tmp2;
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && ft_check_doll(&str[i], lst_before_export, list_env))
		{
			tmp2 = str;
			tmp = ft_check_doll(&str[i], lst_before_export, list_env);
			str[i] = '\0';
			str = ft_strjoin(str, tmp);
			free(tmp2);
		}
		else if (str[i] == '$' && !ft_check_doll(&str[i], lst_before_export, list_env))
		{
			tmp2 = str;
			str[i] = '\0';
			str = ft_strdup(str);
			free(tmp2);
			if (str[0] == '\0')
			{
				str = NULL;
				break;
			}
		}
		i++;
	}
	return (str);
}

int	main(int argc, char **argv, char **env)
{
	int k;
	int i;
	char *line;
	char **str;
	char *tmp;
	line = NULL;
	int	flag;
	int	j;
	t_list *lst_before_export;
	lst_before_export = NULL;
	t_list_arg *list;
	int	flag_break = 0;
	t_list *list_env;
	list_env = NULL;
	ft_list_create(&list_env, env);

	flag = 0;
	int flag_doll = 0;

	write(1, "minishell > ", 12);
	ft_putstr_fd(getcwd(NULL, 0), 1);
	write(1, " > ", 3);
	k = 0;
	int l = 0;
	while (1)
	{
		if ((k = (ft_get_next_line(0, &line)) > 0))
		{
			str = ft_parse_line(list, line);
			free(line);
			line = NULL;
		}
		flag_break = 0; 
		j = 0;
		if (str[0])
        {
            int i = 0;
            int k;
            while (str[0][i] != '\0')
            {
                if (str[0][i] == '=')
				{
					ft_lstadd_back(&lst_before_export, ft_lstnew2(str[0]));
					flag_break = 1; 
				}
                i++;
            }
        }
		if (flag_break == 0)
		{
			if (str[0] && str[0][1])
			{
				while (str[j][0] == '$' && str[j][1] != '?' && !(ft_check_doll(str[j], lst_before_export, list_env)))
				{
					j++;
					if (!str[j])
						break;
					if (str[j][0] == '$' && str[j][1] != '?' && ft_check_doll(str[j], lst_before_export, list_env))
					str[j] = ft_check_doll(str[j], lst_before_export, list_env);
				}
			}
			if (str[j] && ((ft_strcmp(str[j], "export")) == 0))
			{
				j++;
				char **tmp;
				t_list *dst;
				char *s1;
				int i;
				int l;
				if (!str[j])
				{
					tmp = ft_sort_mass(make_str(&list_env, ft_lstsize(list_env)));
					i = 0;
					while (tmp[i])
					{
						ft_putstr_fd("declare -x ", 1);
						l = 0;
						while (tmp[i][l] != '\0')
						{
							write (1, &tmp[i][l], 1);
							if (tmp[i][l] == '=')
								write(1, "\"", 1);
							l++;
						}
						write(1, "\"", 1);
						write(1, "\n", 1);
						i++;
					}
				}
				else if (str[j])
				{
					while (str[j])
					{
						dst = lst_before_export;
						while (dst)
						{
							if (ft_strncmp(str[j], dst->content, ft_strlen_2(dst->content, '=')) == 0)
								ft_lstadd_back(&list_env, ft_lstnew2(dst->content));
							dst = dst->next;					
						}
						j++;
					}
				}
				
			}
			if (str[j] && ((ft_strcmp(str[j], "cd")) == 0))
			{
				flag = 1;
				k = 0;
				flag_exit = 0;
				tmp = getcwd(NULL, 0);
				j++;
				if (!str[j])
				{
					while (env[k])
					{
						if (!(ft_strncmp(env[k], "HOME=", 4)))
						{
							str[j] = ft_strdup(&env[k][5]);
							break ;
						}
						k++;
					}
				}
				while (str[j] && str[j][0] == '$')
				{
					if (ft_check_doll(str[j], lst_before_export, list_env))
					{
						str[j] = ft_check_doll(str[j], lst_before_export, list_env);
						break;
					}
					j++;
				}
				if (str[j] && (k = chdir(str[j])) == -1)
				{
					ft_putstr_fd("minishell: cd: ", 2);
					ft_putstr_fd(str[j], 2);
					ft_putstr_fd(": ", 2);
					ft_putendl_fd(strerror(errno), 2);
					flag_exit = 1;
				}
				else
				{
					k = 0;
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
			else if (str[j] && ((ft_strcmp(str[j], "pwd")) == 0))
			{
				ft_putstr_fd(getcwd(NULL, 0), 1);
				write(1, "\n", 1);
			}
			else if (str[j] && ((ft_strcmp(str[j], "env")) == 0))
			{
				k = 0;
				if (!str[j + 1])
				{
					t_list *tmp;

					tmp = list_env;
					while(tmp)
					{
						if (flag == 0 && (ft_strncmp(tmp->content, "OLDPWD=", 7)) == 0)
							k++;
						ft_putendl_fd(tmp->content, 1);
						tmp = tmp->next;
					}
				}
			}
			else if (str[j] && ((ft_strcmp(str[j], "echo")) == 0))
			{
				j++;
				if (str[j])
				{
					int flag_n = 0;
					if (str[j] && (ft_strcmp(str[j], "-n") == 0))
					{
						flag_n = 1;
						j++;
					}
					while (str[j])
					{
						// while (str[j] && str[j][0] == '$')
						// {
						// 	if (ft_check_doll(str[j], lst_before_export, list_env))
						// 	{
						// 		str[j] = ft_check_doll(str[j], lst_before_export, list_env);
						// 		break;
						// 	}
						// 	j++;
						// }
						str[j] = ft_change_dollar(str[j], lst_before_export, list_env);
						if (str[j])
						{
							write(1, str[j], ft_strlen(str[j]));
							if (str[j + 1])
								write(1, " ", 1);
						}
						j++;
					}
					if (flag_n == 0)
						write(1, "\n", 1);
				}
				else
					write (1, "\n", 1);
			}
			else if (str[j] && ((ft_strcmp(str[j], "$?")) == 0))
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putnbr_fd(flag_exit, 2);
				ft_putendl_fd(": command not found", 2);
			}
			else if (str[j] && ((ft_strcmp(str[j], "exit")) == 0))
			{
				ft_putendl_fd("exit", 2);
				if (str[j])
					flag_exit = ft_atoi(str[j + 1]);
				exit(flag_exit);
			}
			else if (str[j] && ((ft_strcmp(str[j], "unset")) == 0))
			{
				j++;

				ft_unset(&str[j], &lst_before_export);
				ft_unset(&str[j], &list_env);
			}
			else if (str[j])
			{
				int x;

				x = j;
				//str = ft_change_dollar(str, j, lst_before_export, list_env);
				while (str[x] && str[x][1])
				{
					str[x] = ft_change_dollar(str[x], lst_before_export, list_env);
					x++;
				}
				char **str_path;
				DIR *dir;
				struct dirent *entry;
				int	flag2;
				char **env;

				env = make_str(&list_env, ft_lstsize(list_env));
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
						if ((ft_strcmp(str[j], entry->d_name)) == 0)
						{
							flag_exit = ft_pork(str[j], str_path[k], &str[j], env);
							flag2 = 1;
							break ;
						}
					}
					closedir(dir);
					k++;
				}
				if (flag2 == 0)
				{
					flag_exit = ft_pork(str[j], ".", &str[j], env);
					if (flag_exit == 127)
					{
						ft_putstr_fd("minishell: ", 2);
						ft_putstr_fd(str[j], 2);
						ft_putendl_fd(": command not found", 2);
					}
				}
			}
		}
		write(1, "minishell > ", 12);
		ft_putstr_fd(getcwd(NULL, 0), 1);
		write(1, " > ", 3);
	}
	return (0);
}