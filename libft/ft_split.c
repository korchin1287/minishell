/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 14:59:28 by ndreadno          #+#    #+#             */
/*   Updated: 2020/05/27 10:40:59 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_separator(char const *s, char c)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	if (s[i] != c && s[i] != '\0')
		k++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			k++;
		i++;
	}
	return (k);
}

static	size_t	ft_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static	char	*ft_word(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	return ((char *)&s[i]);
}

static	void	*ft_memory_free(char **str)
{
	size_t	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char	**res;
	size_t	i;
	size_t	count_separator;

	i = 0;
	if (!s)
		return (NULL);
	count_separator = ft_separator(s, c);
	res = (char **)malloc(sizeof(char*) * (count_separator + 1));
	if (res == NULL)
		return (NULL);
	res[count_separator] = NULL;
	while (i < count_separator)
	{
		s = ft_word(s, c);
		res[i] = ft_substr(s, 0, ft_len(s, c));
		if (res[i] == NULL)
		{
			return (ft_memory_free(res));
		}
		i++;
		s += ft_len(s, c);
	}
	return (res);
}
