/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 23:03:09 by nofloren          #+#    #+#             */
/*   Updated: 2020/04/30 23:18:07 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = (char*)s;
	while (i < n)
	{
		if ((unsigned char)tmp[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
