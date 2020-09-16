/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 16:41:37 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/16 17:59:08 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen_2(const char *str, char *check)
{
	size_t i;
	size_t k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		k = 0;
		while (check[k])
		{
			if (str[i] == check[k])
				return (i);
			k++;			
		}
		i++;
	}
	return (i);
}



char	*ft_check_doll(char *str, t_list *lst_before_export, t_list *list_env)
{
	int	k;
	t_list *first_dst;
	t_list *first_tmp;

	if (!str)
		return (NULL);
	int count = ft_strlen_2(str, "\\$\'\" <;>| ");
	k = 0;
	first_tmp = list_env;
	while (first_tmp)
	{
		if (ft_strncmp(first_tmp->content, str, count) == 0)
		{
			count = ft_strlen_2(first_tmp->content, "=");
				if (ft_strncmp(first_tmp->content, str, count) == 0)
					return (&first_tmp->content[count + 1]);
		}
		first_tmp = first_tmp->next;
	}
	first_dst = lst_before_export;
	while (first_dst)
	{
		if (ft_strncmp(first_dst->content, str, count) == 0)
		{
			count = ft_strlen_2(first_dst->content, "=");
			if (ft_strncmp(first_dst->content, str, count) == 0)
				return (&first_dst->content[count + 1]);
		}
		first_dst = first_dst->next;
	}
	return (NULL);
}

char	*ft_change_dollar(t_data *data, char *str, char *dst)
{
	char *tmp3;
	int i;
	int count;

	i = 0;
	count = ft_strlen_2(str,   "\\$\'\" <;>| ");
	tmp3 = ft_check_doll(str, data->before_export, data->env);
	if (tmp3)
	{
		i = ft_strlen(dst);
		ft_strcpy(&dst[i], tmp3);
	}	
	return (tmp3);
}
int		ft_dollar(t_data *data, char *str, char *out, int *l)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_change_dollar(data, &str[i + 1], out);
	if (tmp)
		*l += ft_strlen(tmp);
	i += ft_strlen_2(&str[i + 1],  "\\$\'\" <;>| ") + 1;
	return (i);
}
int		ft_len_dollars(char *str, t_list *lst_before_export, t_list *list_env, int k)
{
	int len;
	char *tmp;

	len = 0;
	tmp = ft_check_doll(&str[k + 1], lst_before_export, list_env);
	if (tmp)
		len = ft_strlen(tmp);
	return len;
}