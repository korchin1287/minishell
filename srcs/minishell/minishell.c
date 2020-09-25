/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 15:46:34 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/25 16:12:16 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	int		i;
	int		flag;
	char	*tmp;
	char	*path;
	char	*old;

	flag = 0;
	path = getcwd(NULL, 0);
	path = ft_strjoin(":", path);
	i = 0;
	while(env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			env[i] = ft_strjoin(env[i], path);
		if ((ft_strcmp("OLDPWD", env[i]) == 0) || (ft_strncmp("OLDPWD=", env[i], 7)))
			flag = 1;
		ft_lstadd_back(list_env, ft_lstnew2(env[i]));
		i++;
	}
	if (!flag)
	{
		ft_lstadd_back(list_env, ft_lstnew2("OLDPWD"));
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

void	ft_print_name()
{
	char *minishell;
	
	minishell = getcwd(NULL, 0);
	minishell = ft_strjoin("\e[32mminishell > ", minishell);
	minishell = ft_strjoin(minishell, "\e[0m");
	ft_putstr_fd(minishell, 1);
	ft_putstr_fd("\e[32m > \e[0m", 1);
}

void	ft_shell_init(t_shell *shell)
{
	shell->lst_before_export = NULL;
	shell->list_env = NULL;
	shell->tmp_arg = NULL;
	shell->list_arg = NULL;
	shell->flag_exit = 0;
	shell->flag_cd = 1;
	shell->savestdin = dup(0);
	shell->sevestdout = dup(1);
	shell->flag_redirect = 0;
}

int		ft_what_command(t_shell *shell)
{
	if ((ft_strcmp(shell->list_arg->arg[shell->j], "export")) == 0)
		return (1);
	else if ((ft_strcmp(shell->list_arg->arg[shell->j], "cd")) == 0)
		return (1);
	else if ((ft_strcmp(shell->list_arg->arg[shell->j], "pwd")) == 0)
		return (1);
	else if ((ft_strcmp(shell->list_arg->arg[shell->j], "env")) == 0)
		return (1);
	else if ((ft_strcmp(shell->list_arg->arg[shell->j], "echo")) == 0)
		return (1);
	else if ((ft_strcmp(shell->list_arg->arg[shell->j], "$?")) == 0)
		return (1);
	else if ((ft_strcmp(shell->list_arg->arg[shell->j], "exit")) == 0)
		return (1);
	else if ((ft_strcmp(shell->list_arg->arg[shell->j], "unset")) == 0)
		return (1);
	else
		return (0);
}

void command_minishell(t_shell *shell)
{
	if ((ft_strcmp(shell->list_arg->arg[shell->j], "export")) == 0)
		ft_command_export(shell);				
	else if ((ft_strcmp(shell->list_arg->arg[shell->j], "cd")) == 0)
		ft_command_cd(shell);
	else if ((ft_strcmp(shell->list_arg->arg[shell->j], "pwd")) == 0)
	{
		ft_putstr_fd(getcwd(NULL, 0), 1);
		write(1, "\n", 1);
	}
	else if ((ft_strcmp(shell->list_arg->arg[shell->j], "env")) == 0)
		ft_command_env(shell);
	else if ((ft_strcmp(shell->list_arg->arg[shell->j], "echo")) == 0)
		ft_command_echo(shell);
	else if ((ft_strcmp(shell->list_arg->arg[shell->j], "$?")) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putnbr_fd(shell->flag_exit, 2);
		ft_putendl_fd(": command not found", 2);
	}
	else if ((ft_strcmp(shell->list_arg->arg[shell->j], "exit")) == 0)
	{
		ft_putendl_fd("exit", 2);
		if (shell->list_arg->arg[shell->j])
			shell->flag_exit = ft_atoi(shell->list_arg->arg[shell->j + 1]);
		exit(shell->flag_exit);
	}
	else if ((ft_strcmp(shell->list_arg->arg[shell->j], "unset")) == 0)
		ft_command_unset(shell);
	else
		ft_command_bash(shell);
}

int	main(int argc, char **argv, char **env)
{ 
	t_shell shell;
	
	ft_shell_init(&shell);
	ft_list_create(&shell.list_env, env);
	ft_print_name();
	ft_singnal();
	while (1)
	{
		if (!ft_read_info(&shell))
			continue;
		while (shell.list_arg)
		{
			shell.j = 0;
			ft_parse_list(shell.list_arg, shell.lst_before_export, shell.list_env);
			ft_add_list_before_export(&shell);
			if (shell.list_arg->arg[shell.j])
			{
				if (shell.list_arg->flag_pipe == 1 || shell.list_arg->flag_redir_one == 1 || shell.list_arg->flag_redir_two == 1)
					ft_make_with_pipe(&shell);
				else if (shell.list_arg->flag_redir_one_left == 1)
					ft_make_with_left_redir(&shell);
				else
					command_minishell(&shell);
			}
			if (shell.list_arg->flag_end == 1)
			{
				dup2(shell.savestdin, 0);
				dup2(shell.sevestdout, 1);
			}
			shell.list_arg = shell.list_arg->next;
		}
		dup2(shell.savestdin, 0);
		dup2(shell.sevestdout, 1);
		ft_print_name();
		ft_clear_lst(&shell.tmp_arg);
	}
	return (0);
}