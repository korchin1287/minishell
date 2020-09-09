/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:20:18 by ndreadno          #+#    #+#             */
/*   Updated: 2020/05/24 23:48:05 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char *ptr;

	ptr = (unsigned char *)destination;
	while (n-- > 0)
	{
		*(ptr + n) = (unsigned char)c;
	}
	return (destination);
}
