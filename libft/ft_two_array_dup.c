/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_two_array_dup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 13:47:03 by ndreadno          #+#    #+#             */
/*   Updated: 2020/10/04 14:14:23 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_two_ar_dup(char **str)
{
	int		i;
	char	**res;

	i = 0;
	while (str[i])
		i++;
	res = ft_malloc(sizeof(char *), i + 1);
	i = -1;
	while (str[++i])
		res[i] = ft_strdup(str[i]);
	res[i] = NULL;
	return (res);
}
