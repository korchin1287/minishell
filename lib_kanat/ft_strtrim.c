/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:45:53 by ndreadno          #+#    #+#             */
/*   Updated: 2020/05/25 01:13:21 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_check(const char *s1, const char *set)
{
	int k;
	int i;

	i = 0;
	while (s1[i] != '\0')
	{
		k = 0;
		while (set[k] != '\0')
		{
			if (s1[i] == set[k])
				break ;
			k++;
		}
		if (set[k] == '\0')
			break ;
		i++;
	}
	return (i);
}

static	size_t	ft_check_reverse(int i, const char *s1, const char *set)
{
	int k;

	while (i >= 0)
	{
		k = 0;
		while (set[k] != '\0')
		{
			if (s1[i] == set[k])
				break ;
			k++;
		}
		if (set[k] == '\0')
			break ;
		i--;
	}
	return (i);
}

static	char	*ft_trim(char const *s1, char *dst, int i, int k)
{
	size_t	l;

	l = 0;
	while (i <= k)
	{
		dst[l] = s1[i];
		i++;
		l++;
	}
	dst[l] = '\0';
	return (dst);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		k;
	size_t	len;
	char	*dst;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	i = ft_check(s1, set);
	k = ft_check_reverse(len - 1, s1, set);
	if (s1[i] != '\0')
		dst = (char*)malloc(sizeof(*dst) * (len - (len - k + i) + 2));
	else
		dst = (char*)malloc(sizeof(*dst) * (1));
	if (dst == NULL)
		return (NULL);
	dst = ft_trim(s1, dst, i, k);
	return (dst);
}
