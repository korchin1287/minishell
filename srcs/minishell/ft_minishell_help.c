/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_help.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:35:10 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/15 17:01:34 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_lstadd_back3(t_costl **lst, t_costl *new)
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

t_costl		*ft_lstnew3(char **content)
{
	t_costl *dst;

	dst = (t_costl *)ft_malloc(sizeof(t_costl), 1);
	if (dst)
	{
		dst->content = content;
		dst->next = NULL;
	}
	else
		exit(-1);
	return (dst);
}

char		**make_str(t_list **list_env, int size)
{
	char	**str;
	int		i;
	t_list	*tmp;

	if (!(str = ft_malloc(sizeof(char *), (size + 1))))
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

void		ft_shell_init(t_shell *shell)
{
	shell->lst_before_export = NULL;
	shell->list_env = NULL;
	shell->tmp_arg = NULL;
	shell->tmp_redir = NULL;
	shell->list_arg = NULL;
	shell->str_path = NULL;
	shell->flag_command_bash_not = 0;
	shell->costl = NULL;
	shell->flag_exit = 0;
	shell->flag_cd = 1;
	shell->savestdin = dup(0);
	shell->sevestdout = dup(1);
	shell->flag_redirect = 0;
	shell->flag_stat = 0;
	shell->count = 0;
}

int			ft_what_command(t_shell *shell)
{
	if ((shell->list_arg->arg[shell->j][0] == '\0' ||
		(ft_strcmp(shell->list_arg->arg[shell->j], "export")) == 0)
		&& (ft_strcmp(shell->list_arg->arg2[shell->j], "export")) == 0)
		return (1);
	else if ((shell->list_arg->arg[shell->j][0] == '\0' ||
		(ft_strcmp(shell->list_arg->arg[shell->j], "cd")) == 0)
		&& (ft_strcmp(shell->list_arg->arg2[shell->j], "cd")) == 0)
		return (1);
	else if ((ft_strcmp(shell->list_arg->arg2[shell->j], "pwd")) == 0)
		return (1);
	else if ((ft_strcmp(shell->list_arg->arg2[shell->j], "env")) == 0)
		return (1);
	else if ((ft_strcmp(shell->list_arg->arg2[shell->j], "echo")) == 0)
		return (1);
	else if ((shell->list_arg->arg[shell->j][0] == '\0' ||
		(ft_strcmp(shell->list_arg->arg[shell->j], "exit")) == 0)
		&& (ft_strcmp(shell->list_arg->arg2[shell->j], "exit")) == 0)
		return (1);
	else if ((shell->list_arg->arg[shell->j][0] == '\0' ||
		(ft_strcmp(shell->list_arg->arg[shell->j], "unset")) == 0)
		&& (ft_strcmp(shell->list_arg->arg2[shell->j], "unset")) == 0)
		return (1);
	else
		return (0);
}
