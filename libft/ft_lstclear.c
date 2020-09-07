/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 03:01:53 by nofloren          #+#    #+#             */
/*   Updated: 2020/05/11 00:38:58 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *dst;

	if (!del)
		return ;
	while (*lst)
	{
		dst = *lst;
		del((*lst)->content);
		*lst = dst->next;
		free(dst);
	}
	*lst = NULL;
}
