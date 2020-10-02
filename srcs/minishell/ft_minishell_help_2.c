/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_help_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:38:22 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/02 15:45:22 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exitstatus(t_shell *shell, int flag_exit)
{
	char *str1;

	str1 = ft_strjoin("?=", ft_itoa(flag_exit));
	if (!(ft_check_list_for_export(&shell->lst_before_export, str1)))
		ft_lstadd_back(&shell->lst_before_export, ft_lstnew2(str1));
	shell->flag_exit = flag_exit;
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

	if ((minishell = getcwd(NULL, 0)) == NULL)
		exit(2);
	tmp = minishell;
	minishell = ft_strjoin("\e[32mminishell > ", minishell);
	ft_free_null(tmp);
	tmp = minishell;
	minishell = ft_strjoin(minishell, "\e[0m");
	ft_free_null(tmp);
	ft_putstr_fd(minishell, 1);
	ft_putstr_fd("\e[32m > \e[0m", 1);
	ft_free_null(minishell);
}
