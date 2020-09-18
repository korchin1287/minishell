/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 16:41:37 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/18 22:24:15 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen_3(const char *str, char c)
{
	size_t i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

size_t	ft_count_dollar(const char *str)
{
	size_t i;
	size_t k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		k = 0;
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]))
			return (i);
		i++;
	}
	return (i);
}



char	*ft_check_doll(char *str, t_list *lst_before_export, t_list *list_env)
{
	t_list *tmp;
	int count;

	if (!str)
		return (NULL);
	count = ft_count_dollar(str);
	tmp = list_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, str, count) == 0)
		{
			count = ft_strlen_3(tmp->content, '=');
				if (ft_strncmp(tmp->content, str, count) == 0)
					return (&tmp->content[count + 1]);
		}
		tmp = tmp->next;
	}
	tmp = lst_before_export;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, str, count) == 0)
		{
			count = ft_strlen_3(tmp->content, '=');
			if (ft_strncmp(tmp->content, str, count) == 0)
				return (&tmp->content[count + 1]);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_change_dollar(t_data *data, char *str, char *dst)
{
	char *tmp3;
	int i;
	int count;

	i = 0;
	count = ft_count_dollar(str);
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
	i += ft_count_dollar(&str[i + 1]) + 1;
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
	return (len);
}