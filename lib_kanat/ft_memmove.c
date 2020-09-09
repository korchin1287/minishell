/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 11:52:46 by ndreadno          #+#    #+#             */
/*   Updated: 2020/05/25 00:09:22 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*ptrd;
	unsigned char	*ptrs;

	i = 0;
	ptrd = (unsigned char *)dst;
	ptrs = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (len == 0)
		return (dst);
	if (ptrd > ptrs)
	{
		while (len-- > 0)
			ptrd[len] = ptrs[len];
	}
	else
	{
		while (i < len)
		{
			ptrd[i] = ptrs[i];
			i++;
		}
	}
	return (dst);
}
