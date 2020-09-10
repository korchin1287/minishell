/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 13:18:18 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/10 13:58:45 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_trim(char *res, char *str, char *trim, int len)
{
	int i;
	int l;
	int k;

	i = 0;
	l = -1;
	k = -1;
	while(++k < len)
	{
		l = -1;
		while (trim[++l])
			if (str[i] == trim[l])
				i++;
		res[k] = str[i];
		i++;
	}
	res[k] = '\0';
	return (res);
}

char		*ft_strtrim_new(char *str, char *trim)
{
	char *res;
	int i;
	int l;
	int len;
	int count;

	i = -1;
	l = -1;
	count = 0;
	while (str[++i])
	{
		l = -1;
		while (trim[++l])
			if (str[i] == trim[l])
				count++;
	}
	len = ft_strlen(str) - count;
	if (!(res = (char *)malloc(sizeof(res) * (len + 1))))
		return (NULL);
	res = ft_trim(res, str, trim, len);
	return (res);
}