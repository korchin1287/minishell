/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 01:38:16 by nofloren          #+#    #+#             */
/*   Updated: 2020/05/06 01:42:34 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *dst;

	dst = malloc(sizeof(t_list));
	if (dst)
	{
		dst->content = content;
		dst->next = NULL;
	}
	else
		return (NULL);
	return (dst);
}
