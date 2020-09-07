/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 23:18:34 by nofloren          #+#    #+#             */
/*   Updated: 2020/05/02 03:20:09 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*dest;
	unsigned char	*src;
	size_t			i;

	dest = (unsigned char*)s1;
	src = (unsigned char*)s2;
	i = 0;
	if (n != 0)
	{
		while (i < n)
		{
			if (dest[i] != src[i])
				return (dest[i] - src[i]);
			i++;
		}
	}
	return (0);
}
