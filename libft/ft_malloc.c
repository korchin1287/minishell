/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 12:00:22 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/27 12:08:25 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t type_size, size_t size)
{
	void *ptr;
	if ((ptr = malloc(type_size * size)) == NULL)
	{
		write(2, "malloc error\n", 14);
		exit(2);
	}
	return (ptr);
}
