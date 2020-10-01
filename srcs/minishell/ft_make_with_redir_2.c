/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_with_redir_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 20:06:34 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/30 15:55:24 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_help_this(t_shell *shell)
{
	if (shell->costl)
		ft_make_first_argv(shell);
}

void	ft_make_first_argv_help(t_shell *shell, char **str)
{
	t_costl *tmp;
	int i;
	int k;
	
	i = -1;
	k = 0;
	while (shell->list_arg->arg[++i])
		str[i] = ft_strdup(shell->list_arg->arg[i]);
	tmp = shell->costl;
	while (tmp)
	{
		k = -1;
		while (tmp->content[++k])
			str[i++] = ft_strdup(tmp->content[k]);
		tmp = tmp->next;
	}
	str[i] = NULL;
	free(shell->list_arg->arg);
	shell->list_arg->arg = str;
}

void	ft_make_first_argv(t_shell *shell)
{
	int		count;
	char	**str;
	t_costl	*tmp;

	count = ft_cout_mas(shell->list_arg->arg);
	tmp = shell->costl;
	while (tmp)
	{
		count += ft_cout_mas(tmp->content);
		tmp = tmp->next;
	}
	if (!(str = malloc(sizeof(char *) * (count + 1))))
		exit(-1);
	ft_make_first_argv_help(shell, str);
}

void	ft_open_file_redir(t_shell *shell, t_list_arg **tmp)
{
	shell->flag_redirect = 1;
	shell->fd_file = -1;
	while ((*tmp)->flag_redir_one == 1 || (*tmp)->flag_redir_two == 1)
	{
		ft_parse_list_line(shell, (*tmp)->next);
		if ((*tmp)->flag_redir_one == 1)
			shell->fd_file = open((*tmp)->next->arg[0], O_CREAT | O_RDWR | O_TRUNC, 0666);
		else if ((*tmp)->flag_redir_two == 1)
			shell->fd_file = open((*tmp)->next->arg[0], O_CREAT | O_RDWR| O_APPEND, 0666);
		if (shell->fd_file == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd((*tmp)->next->arg[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
			ft_exitstatus(shell, 1);
		}
		shell->count++;
		if ((*tmp)->next->arg[1])
			ft_lstadd_back3(&shell->costl, ft_lstnew3(&((*tmp)->next->arg[1])));
		(*tmp) = (*tmp)->next;
	}
}