/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:38:00 by nofloren          #+#    #+#             */
/*   Updated: 2020/05/11 00:50:06 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	size_t	x;
	size_t	i;
	char	*tmp;

	x = num * size;
	tmp = (char*)malloc(x);
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < x)
	{
		tmp[i] = 0;
		i++;
	}
	return ((void*)tmp);
}
