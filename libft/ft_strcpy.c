/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 21:45:27 by ndreadno          #+#    #+#             */
/*   Updated: 2020/10/04 16:44:45 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcpy(char *dst, char *src)
{
	int i;

	i = -1;
	while (src[++i] != '\0')
		dst[i] = src[i];
	dst[i] = '\0';
}
