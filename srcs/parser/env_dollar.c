/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 18:36:22 by ndreadno          #+#    #+#             */
/*   Updated: 2020/10/12 16:38:31 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_len_dollars(char *str, t_list *lst_bfe, t_list *list_env, int k)
{
	int		len;
	int		count;
	char	*tmp;

	len = 0;
	count = ft_count_dollar(&str[k + 1]);
	tmp = ft_check_doll(&str[k + 1], list_env, count);
	if (!tmp)
		tmp = ft_check_doll(&str[k + 1], lst_bfe, count);
	if (tmp)
		len = ft_strlen(tmp);
	else if (g_status == 1)
		len = 1;
	return (len);
}

int		ft_dollar(t_data *data, char *str, char *out, int *l)
{
	char	*tmp;
	int		i;
	int		ll;
	char	*s;

	i = 0;
	tmp = ft_change_dollar(data, &str[i + 1], out);
	if (tmp)
		*l += ft_strlen(tmp);
	if (((s = ft_strchr(tmp, '=')) != NULL) &&
		(ll = ft_check_cmd(data->arg_list)))
		(*data->list)->flag_disable_char = ft_size_list(data->arg_list) + 1;
	i += ft_count_dollar(&str[i + 1]) + 1;
	return (i);
}
