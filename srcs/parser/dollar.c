/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 16:41:37 by ndreadno          #+#    #+#             */
/*   Updated: 2020/10/12 13:29:19 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_count_dollar(const char *str)
{
	size_t i;
	size_t k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		k = 0;
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_' &&
			str[i] != '?')
			return (i);
		i++;
	}
	return (i);
}

char	*ft_check_doll(char *str, t_list *lst, int count)
{
	t_list *tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, str, count) == 0 &&
			(tmp->content[count] == '=' || tmp->content[count] == '\0'))
		{
			return (&tmp->content[count + 1]);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_change_dollar(t_data *data, char *str, char *dst)
{
	char	*tmp3;
	int		i;
	int		count;

	i = 0;
	if (!str)
		return (NULL);
	count = ft_count_dollar(str);
	tmp3 = ft_check_doll(str, data->env, count);
	if (!tmp3)
		tmp3 = ft_check_doll(str, data->before_export, count);
	if (tmp3)
	{
		i = ft_strlen(dst);
		if (g_status != 1)
		{
			ft_strcpy(&dst[i], tmp3);
		}
		else
		{
			ft_strcpy(&dst[i], "1");
		}
	}
	return (tmp3);
}
