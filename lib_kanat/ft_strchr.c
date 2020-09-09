/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 13:23:17 by ndreadno          #+#    #+#             */
/*   Updated: 2020/05/12 22:56:40 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	size_t		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)ch)
			break ;
		i++;
	}
	if (str[i] != (char)ch)
		return (NULL);
	return ((char*)&str[i]);
}
