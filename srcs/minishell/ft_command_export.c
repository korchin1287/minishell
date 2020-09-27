/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:26:17 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/26 18:11:00 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_check_list_for_export(t_shell *shell, t_list **list, char *str)
{
	t_list *tmp;
	char *tmp_2;

	tmp = *list;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if ((ft_strncmp(tmp->content, str, ft_strlen_3(str, '=')) == 0) && (ft_strncmp(tmp->content, str, ft_strlen_3(tmp->content, '=')) == 0))
		{
			if (!ft_strchr(str, '='))
				return (1);
			tmp_2 = tmp->content;
			tmp->content = ft_strdup(str);
			free(tmp_2);
			tmp_2= NULL;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_print_export(t_shell *shell)
{
	char **tmp;
	int i;
	int l;
	int len;

	tmp = ft_sort_mass(make_str(&shell->list_env, ft_lstsize(shell->list_env)));
	i = 0;
	while (tmp[i])
	{
		len = ft_strlen_3(&tmp[i][0], '=');
		ft_putstr_fd("declare -x ", 1);
		write (1, &tmp[i][0], ++len);
		if (tmp[i][len - 1] == '=')
		{
			l = len;
			write(1, "\"", 1);
			while (tmp[i][l] != '\0')
			{
				write (1, &tmp[i][l], 1);
				l++;
			}
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}

int	ft_add_env_from_export(t_shell *shell)
{
	t_list *dst;
	
	dst = shell->lst_before_export;
	while (dst)
	{
		if ((ft_strncmp(shell->list_arg->arg[shell->j], dst->content, ft_strlen_3(dst->content, '=')) == 0))
		{
			ft_lstadd_back(&shell->list_env, ft_lstnew2(dst->content));
			ft_unset(shell, &shell->list_arg->arg[shell->j], &shell->lst_before_export);
			return (1);
		}
		dst = dst->next;					
	}
	return (0);
}

int		ft_check_name(char *str, char check)
{
	int i;
	int check_before;

	i = 0;
	check_before = ft_strlen_3(str, check);
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (str[i] != '\0' && i < check_before)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
void    ft_command_export(t_shell *shell)
{
	shell->j++;
	char **tmp;
	t_list *tmp2;
	char *s1;
	int i;
	tmp = shell->list_arg->arg;
	
	if (!shell->list_arg->arg[shell->j])
		ft_print_export(shell);
	while (tmp[shell->j])
	{
		int check;

		check = ft_check_name(tmp[shell->j], '=');
		if (shell->list_arg->flag_disable_char == 0 && check)
		{
			if (!ft_check_list_for_export(shell, &shell->list_env, tmp[shell->j]))
			{
				if (!ft_add_env_from_export(shell))
					ft_lstadd_back(&shell->list_env, ft_lstnew2(tmp[shell->j]));
			}
		}
		else if (!check || shell->list_arg->flag_disable_char)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("export: \'", 2);
			ft_putstr_fd(tmp[shell->j], 2);
			ft_putendl_fd("\': not a valid identifier", 2);
			ft_make_wexitstatus(shell, 1);
		}
		shell->j++;
	}
}