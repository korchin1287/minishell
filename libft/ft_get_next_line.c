/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:30:49 by ndreadno          #+#    #+#             */
/*   Updated: 2020/08/26 11:24:33 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

int				ft_get_next_line(int fd, char **line)
{
	char		buf[2];
	int			flag;
	char		*tmp;
	int			read_size;

	flag = 1;
	if ((*line = ft_strdup("")) == NULL)
		return (-1);
	while (flag == 1 && (read_size = read(fd, buf, 1)))
	{
		buf[read_size] = '\0';
		if (buf[0] == '\n')
		{
			buf[0] = '\0';
			flag = 0;
		}
		tmp = *line;
		if ((*line = ft_strjoin(*line, buf)) == NULL)
		{
			free(tmp);
			return (-1);
		}
		free(tmp);
	}
	return (read_size);
}
