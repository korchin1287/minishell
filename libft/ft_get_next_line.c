/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:30:49 by ndreadno          #+#    #+#             */
/*   Updated: 2020/10/02 17:25:41 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

static char			*join(char **line, char *buf, int *read_size)
{
	char *tmp;
	char *c;

	tmp = *line;
	c = buf;
	if (*read_size == 0 && buf[0] != '\0')
	{
		(*read_size)++;
		c = "\0";
	}
	if ((*line = ft_strjoin(*line, c)) == NULL)
	{
		ft_free_null((void **)&tmp);
		return (NULL);
	}
	ft_free_null((void **)&tmp);
	return (*line);
}

int					ft_get_next_line(int fd, char **line)
{
	char		buf[2];
	int			flag;
	int			read_size;

	flag = 1;
	if ((*line = ft_strdup("")) == NULL)
		return (-1);
	ft_bzero(buf, 1);
	while (flag == 1 && ((read_size = read(fd, buf, 1)) || buf[0] != '\0'))
	{
		if (buf[0] == '\n')
		{
			buf[0] = '\0';
			flag = 0;
		}
		if (join(line, buf, &read_size) == NULL)
			return (-1);
	}
	return (read_size);
}
