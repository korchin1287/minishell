/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:25:51 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/04 16:43:14 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew2(char *content)
{
	t_list *dst;

	dst = (t_list *)ft_malloc(sizeof(t_list), 1);
	if (dst)
	{
		dst->content = ft_strdup(content);
		dst->next = NULL;
	}
	else
		return (NULL);
	return (dst);
}

void	ft_list_create_help(t_list **list_env, char **path, int f_p, int f)
{
	char *tmp;

	tmp = ft_getcwd();
	if (!f_p)
		ft_lstadd_back(list_env, ft_lstnew2(ft_strjoin("PWD=",
			tmp)));
	if (!f)
		ft_lstadd_back(list_env, ft_lstnew2("OLDPWD"));
	free(*path);
	ft_free_null((void **)&tmp);
}

void	ft_list_create(t_list **list_env, char **env)
{
	int		i;
	int		flag;
	int		flag_pwd;
	char	*path;
	char	*tmp;

	flag = 0;
	flag_pwd = 0;
	tmp = ft_getcwd();
	path = ft_strjoin(":", tmp);
	ft_free_null((void **)&tmp);
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			env[i] = ft_strjoin(env[i], path);
		if ((ft_strcmp("OLDPWD", env[i]) == 0) ||
			(ft_strncmp("OLDPWD=", env[i], 7)))
			flag = 1;
		if (!(ft_strncmp(env[i], "PWD=", 4)))
			flag_pwd = 1;
		ft_lstadd_back(list_env, ft_lstnew2(env[i]));
	}
	ft_list_create_help(list_env, &path, flag_pwd, flag);
}
