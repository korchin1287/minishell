/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:26:17 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/14 17:22:37 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_print_export(t_shell *shell)
{
	char	**tmp;
	int		i;
	int		l;
	int		len;
	char	**map;

	map = make_str(&shell->list_env, ft_lstsize(shell->list_env));
	tmp = ft_sort_mass(map);
	i = -1;
	while (tmp[++i])
	{
		len = ft_strlen_3(&tmp[i][0], '=');
		ft_putstr_fd("declare -x ", 1);
		write(1, &tmp[i][0], ++len);
		if (tmp[i][len - 1] == '=')
		{
			l = len;
			write(1, "\"", 1);
			while (tmp[i][l] != '\0')
				write(1, &tmp[i][l++], 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
	}
	ft_free_str(&map);
}

static int	ft_add_env_from_export(t_shell *shell)
{
	t_list *dst;

	dst = shell->lst_before_export;
	while (dst)
	{
		if ((ft_strncmp(shell->list_arg->arg2[shell->j], dst->content,
			ft_strlen_3(dst->content, '=')) == 0))
		{
			ft_lstadd_back(&shell->list_env, ft_lstnew2(dst->content));
			ft_unset(shell, &shell->list_arg->arg2[shell->j],
				&shell->lst_before_export);
			return (1);
		}
		dst = dst->next;
	}
	return (0);
}

int			ft_check_name(char *str, char check)
{
	int	i;
	int	check_before;

	i = 0;
	check_before = ft_strlen_3(str, check);
	if (!ft_isalpha(str[i]) && str[i] != '_' && str[i] != '\b')
		return (0);
	while (str[i] != '\0' && i < check_before)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	ft_command_export_error(t_shell *shell, char **tmp)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("export: \'", 2);
	ft_putstr_fd(tmp[shell->j], 2);
	ft_putendl_fd("\': not a valid identifier", 2);
	ft_exitstatus(shell, 1);
}

void		ft_command_export(t_shell *shell)
{
	char	**tmp;
	int		check;

	shell->j++;
	tmp = shell->list_arg->arg2;
	ft_exitstatus(shell, 0);
	if (!shell->list_arg->arg2[shell->j])
		ft_print_export(shell);
	while (tmp[shell->j])
	{
		check = ft_check_name(tmp[shell->j], '=');
		if ((!shell->list_arg->flag_disable_char &&
			shell->list_arg->flag_disable_char - 1 != shell->j) && check)
		{
			if (!ft_check_list_for_export(&shell->list_env, tmp[shell->j]))
				if (!ft_add_env_from_export(shell))
					ft_lstadd_back(&shell->list_env, ft_lstnew2(tmp[shell->j]));
		}
		else if (!check || shell->list_arg->flag_disable_char)
			ft_command_export_error(shell, tmp);
		shell->j++;
	}
}
