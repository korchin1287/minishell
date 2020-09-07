/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 00:55:30 by nofloren          #+#    #+#             */
/*   Updated: 2020/05/11 00:40:04 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list *newdst;
	t_list *first_dst;

	if (!lst)
		return (NULL);
	first_dst = NULL;
	while (lst)
	{
		newdst = ft_lstnew(lst->content);
		if (!newdst)
		{
			ft_lstclear(&first_dst, del);
			return (NULL);
		}
		newdst->content = f(lst->content);
		ft_lstadd_back(&first_dst, newdst);
		lst = lst->next;
	}
	return (first_dst);
}
