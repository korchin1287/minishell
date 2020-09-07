/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 23:51:16 by nofloren          #+#    #+#             */
/*   Updated: 2020/05/05 01:57:16 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_make_str(char const *str, int len)
{
	int		i;
	char	*dst;

	dst = (char*)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static int	ft_w_count(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			count++;
		}
		if (s[i] == '\0')
			return (count);
		i++;
	}
	return (count);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		k;
	int		j;
	char	**mas;

	if (!s || !(mas = (char**)malloc(sizeof(char*) * (ft_w_count(s, c) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		k = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (i > k)
		{
			mas[j] = ft_make_str(&s[k], i - k);
			j++;
		}
	}
	mas[j] = NULL;
	return (mas);
}
