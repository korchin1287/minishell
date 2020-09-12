/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 13:18:18 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/12 14:46:17 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_trim(char *res, char *str, char trim, int len)
{
	int i;
	int l;
	int k;

	i = 0;
	l = -1;
	k = -1;
	while(++k < len)
	{
		while (str[i] == trim)
				i++;
		res[k] = str[i++];
	}
	res[k] = '\0';
	return (res);
}

char		*ft_strtrim_char(char *str, char trim)
{
	char *res;
	int i;
	int len;
	int count;

	i = 0;
	count = 0;
	while (str[i])
		while (str[i++] == trim)
			count++;
	len = ft_strlen(str) - count;
	if (!(res = (char *)malloc(sizeof(res) * (len + 1))))
		return (NULL);
	res = ft_trim(res, str, trim, len);
	return (res);
}