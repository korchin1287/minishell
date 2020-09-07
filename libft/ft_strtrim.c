/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 01:42:27 by nofloren          #+#    #+#             */
/*   Updated: 2020/05/05 01:44:30 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_set(char c, char const *set)
{
	int				i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char				*ft_strtrim(char const *s1, char const *set)
{
	int				i;
	int				j;
	unsigned int	x;
	char			*dst;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && ft_set(s1[i], set))
		i++;
	j = ft_strlen(s1) - 1;
	while (j != -1 && ft_set(s1[j], set))
		j--;
	if (!*s1 || (char*)&s1[i] == (char*)&s1[j])
		x = 2;
	else
		x = (char*)&s1[j] - (char*)&s1[i] + 2;
	dst = malloc(sizeof(char) * x);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, (char*)&s1[i], x);
	return (dst);
}
