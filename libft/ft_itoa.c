/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 03:28:12 by nofloren          #+#    #+#             */
/*   Updated: 2020/05/11 01:58:53 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		ft_len(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i = 1;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char				*ft_itoa(int n)
{
	size_t	len;
	size_t	i;
	char	*str;
	long	nb;

	len = ft_len(n);
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	nb = n;
	if (n < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	if (n == 0)
		str[0] = '0';
	i = 1;
	while (nb != 0)
	{
		str[len - i] = (nb % 10) + '0';
		nb = nb / 10;
		i++;
	}
	str[len] = '\0';
	return (str);
}
