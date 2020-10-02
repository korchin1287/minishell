/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_null.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:07:15 by ndreadno          #+#    #+#             */
/*   Updated: 2020/10/02 15:45:11 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_null(void *var)
{
	void **tmp;
	tmp = &var;
	free(*tmp);
	*tmp = NULL;
}