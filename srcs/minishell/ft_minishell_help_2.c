/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_help_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:38:22 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/04 16:42:45 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exitstatus(t_shell *shell, int flag_exit)
{
	char *str1;
	char *tmp;

	tmp = ft_itoa(flag_exit);
	str1 = ft_strjoin("?=", tmp);
	if (!(ft_check_list_for_export(&shell->lst_before_export, str1)))
		ft_lstadd_back(&shell->lst_before_export, ft_lstnew2(str1));
	shell->flag_exit = flag_exit;
	ft_free_null((void **)&tmp);
	ft_free_null((void **)&str1);
}

t_costl	*ft_lstlast3(t_costl *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_print_name(void)
{
	char *minishell;
	char *tmp;

	ft_putstr_fd("\e[32mminishell > ", 1);
	minishell = ft_getcwd();
	ft_putstr_fd(minishell, 1);
	ft_putstr_fd("\e[0m", 1);
	ft_putstr_fd("\e[32m > \e[0m", 1);
	ft_free_null((void **)&minishell);
}
