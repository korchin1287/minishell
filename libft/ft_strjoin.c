/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:26:12 by ndreadno          #+#    #+#             */
/*   Updated: 2020/08/26 11:27:18 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	ii;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	ii = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if ((dest = (char*)malloc(sizeof(*dest) * (len + 1))) == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[ii] != '\0')
	{
		dest[i] = s2[ii];
		i++;
		ii++;
	}
	dest[i] = '\0';
	return (dest);
}
