/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 15:46:34 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/30 16:20:30 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exitstatus(t_shell *shell, int flag_exit)
{
	if (!ft_check_list_for_export(shell, &shell->lst_before_export, ft_strjoin("?=", ft_itoa(flag_exit))))
		ft_lstadd_back(&shell->lst_before_export, ft_lstnew2(ft_strjoin("?=", ft_itoa(flag_exit))));
	shell->flag_exit = flag_exit;
}

int 	ft_cout_mas(char **str)
{
	int i;

	i = 0;
	while (str[i])
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

t_costl	*ft_lstlast3(t_costl *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
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

void	ft_lstadd_back3(t_costl **lst, t_costl *new)
{
	t_costl *dst;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	dst = ft_lstlast3(*lst);
	dst->next = new;
}

t_costl	*ft_lstnew3(char **content)
{
	t_costl *dst;

	dst = (t_costl *)malloc(sizeof(t_costl));
	if (dst)
	{
		dst->content = content;
		dst->next = NULL;
	}
	else
		exit (-1);
	return (dst);
}

void	ft_list_create(t_list **list_env, char **env)
{
	int		i;
	int		flag;
	int		flag_pwd;
	char	*tmp;
	char	*path;
	char	*old;

	flag = 0;
	flag_pwd = 0;
	path = getcwd(NULL, 0);
	path = ft_strjoin(":", path);
	i = 0;
	while(env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			env[i] = ft_strjoin(env[i], path);
		if ((ft_strcmp("OLDPWD", env[i]) == 0) || (ft_strncmp("OLDPWD=", env[i], 7)))
			flag = 1;
		if (!(ft_strncmp(env[i], "PWD=", 4)))
			flag_pwd = 1;
		ft_lstadd_back(list_env, ft_lstnew2(env[i]));
		i++;
	}
	if (!flag_pwd)
		ft_lstadd_back(list_env, ft_lstnew2(ft_strjoin("PWD=", getcwd(NULL, 0))));
	if (!flag)
		ft_lstadd_back(list_env, ft_lstnew2("OLDPWD"));
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

void	ft_exit(t_shell *shell)
{
	int i;

	ft_putendl_fd("exit", 2);
	if (shell->list_arg->arg[shell->j + 1])
	{	
		i = 0;
		while (shell->list_arg->arg[shell->j + 1][i] != '\0')
		{
			if (!ft_isdigit(shell->list_arg->arg[shell->j + 1][i++]))
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(shell->list_arg->arg[shell->j + 1], 2);
				ft_putendl_fd(": numeric argument required", 2);
				exit(255);
			}
		}
		ft_exitstatus(shell, ft_atoi(shell->list_arg->arg[shell->j + 1]));
	}
	if (shell->list_arg->arg[shell->j + 1] && shell->list_arg->arg[shell->j + 2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		ft_exitstatus(shell, 1);
		return;
	}
	exit(shell->flag_exit);
}

void	ft_print_name()
{
	char *minishell;
	
	minishell = getcwd(NULL, 0);
	minishell = ft_strjoin("\e[32mminishell > ", minishell);
	minishell = ft_strjoin(minishell, "\e[0m");
	ft_putstr_fd(minishell, 1);
	ft_putstr_fd("\e[32m > \e[0m", 1);
	free(minishell);
}

void	ft_shell_init(t_shell *shell)
{
	shell->lst_before_export = NULL;
	shell->list_env = NULL;
	shell->tmp_arg = NULL;
	shell->list_arg = NULL;
	shell->flag_command_bash_not = 0;
	shell->costl = NULL;
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
		ft_exitstatus(shell, 0);
	}
	else if ((ft_strcmp(shell->list_arg->arg[shell->j], "env")) == 0)
		ft_command_env(shell);
	else if ((ft_strcmp(shell->list_arg->arg[shell->j], "echo")) == 0)
		ft_command_echo(shell);
	else if ((ft_strcmp(shell->list_arg->arg[shell->j], "exit")) == 0)
		ft_exit(shell);
	else if ((ft_strcmp(shell->list_arg->arg[shell->j], "unset")) == 0)
		ft_command_unset(shell);
	else
		ft_command_bash(shell);
}

void	ft_before_while(t_shell *shell, char **env)
{
	process = 0;
	ft_shell_init(shell);
	ft_list_create(&shell->list_env, env);
	ft_print_name();
	ft_singnal();
	ft_exitstatus(shell, shell->flag_exit);
}

void	ft_while_help(t_shell *shell)
{
	if (shell->costl)
	{
		free(shell->costl);
		shell->costl = NULL;
	}
	if (shell->list_arg->flag_end == 1)
		shell->j = 0;
	ft_parse_list_line(shell, shell->list_arg);
	ft_add_list_before_export(shell);
	if (shell->list_arg->arg[shell->j] || (!shell->list_arg->arg[shell->j] && 
		(shell->list_arg->flag_pipe == 1 || shell->list_arg->flag_redir_one == 1 
		|| shell->list_arg->flag_redir_two == 1)))
	{
		if (shell->list_arg->flag_pipe == 1)
			shell->flag_exit = ft_make_with_pipe(shell);
		else if (shell->list_arg->flag_redir_one == 1 || shell->list_arg->flag_redir_two == 1)
			shell->flag_exit = ft_make_with_redir(shell);
		else if (shell->list_arg->flag_redir_one_left == 1)
			ft_make_with_left_redir(shell);
		else
			command_minishell(shell);
	}
}

void	ft_end_while(t_shell *shell)
{
	dup2(shell->savestdin, 0);
	dup2(shell->sevestdout, 1);
	ft_print_name();
	ft_clear_lst(&shell->tmp_arg);
}

int	main(int argc, char **argv, char **env)
{ 
	t_list *tmp;
	t_shell shell;

	ft_before_while(&shell, env);
	while (1)
	{
		if (!ft_read_info(&shell))
			continue;
		shell.j = 0;
		while (shell.list_arg)
		{
			ft_while_help(&shell);
			if (shell.list_arg->flag_end == 1)
			{
				dup2(shell.savestdin, 0);
				dup2(shell.sevestdout, 1);
			}
			shell.list_arg = shell.list_arg->next;
		}
		ft_end_while(&shell);
	}
	return (0);
}