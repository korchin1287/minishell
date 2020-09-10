/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:25:14 by ndreadno          #+#    #+#             */
/*   Updated: 2020/06/01 12:44:24 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	m;

	i = 0;
	j = 0;
	m = ft_strlen(little);
	if (m == 0)
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		if (big[i] == little[0])
			while (big[i] == little[j] && i < len && big[i] != '\0')
			{
				i++;
				j++;
				if (j == m)
					return ((char *)&big[i - j]);
			}
		i = i - j;
		j = 0;
		i++;
	}
	return (NULL);
}
