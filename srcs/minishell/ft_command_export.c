/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:26:17 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/19 14:00:38 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_export(t_shell *shell)
{
    shell->j++;
    char **tmp;
    t_list *dst;
    char *s1;
    int i;
    int l;
    tmp = shell->list_arg->arg;
    l = shell->j;
    while (tmp[l])
    {
        int i = 0;

        while (tmp[l][i] != '\0')
        {
            if (tmp[l][i] == '=' && shell->list_arg->flag_disable_char == 0)
            {
                ft_lstadd_back(&shell->list_env, ft_lstnew2(tmp[l]));
            }
            i++;
        }
        l++;
    }
    if (!shell->list_arg->arg[shell->j])
    {
        tmp = ft_sort_mass(make_str(&shell->list_env, ft_lstsize(shell->list_env)));
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
    else if (shell->list_arg->arg[shell->j])
    {
        while (shell->list_arg->arg[shell->j])
        {
            dst = shell->lst_before_export;
            while (dst)
            {
                if (ft_strncmp(shell->list_arg->arg[shell->j], dst->content, ft_strlen_3(dst->content, '=')) == 0)
                    ft_lstadd_back(&shell->list_env, ft_lstnew2(dst->content));
                dst = dst->next;					
            }
            shell->j++;
        }
    }
}