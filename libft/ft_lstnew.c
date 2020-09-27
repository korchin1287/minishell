/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 01:38:16 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/27 12:11:32 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *dst;

	dst = ft_malloc(sizeof(t_list), 1);
	if (dst)
	{
		dst->content = content;
		dst->next = NULL;
	}
	else
		return (NULL);
	return (dst);
}
