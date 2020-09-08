/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 02:51:00 by nofloren          #+#    #+#             */
/*   Updated: 2020/09/08 20:03:35 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int i;
	int rez;
	int k;

	if (!str)
		return (0);
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	k = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			k = -k;
		i++;
	}
	rez = 0;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		rez = rez * 10 + (str[i] - '0');
		i++;
	}
	return (rez * k);
}
