/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_qual.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:53:24 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/29 13:53:54 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_cmd(t_tmp_list *list)
{
	
	if (list)
		return (ft_strcmp(list->str, "export"));
	return (1);
}

int	ft_check_char_qual(t_data *data, char *str, int k, char flag)
{
	int i;
	int export;

	i = k;
	if (k == 0)
		return (0);
	i = k;
	export = ft_check_cmd(data->arg_list); 
	while (str[--i] != ' ' && i >=0)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && export)
			return (0);
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '\'' && str[i] != '\"' && export == 0)
			return (0);
		if (str[i] == '\'' && str[i] != flag)
			return (0);
		if (str[i] == '\"' && str[i] != flag)
			return (0);
	}
	if (ft_isalpha(str[i + 1]) == 0 && str[i + 1] != '_' && export != 0)
		return (0);
	if (!ft_isalnum(str[i + 1]) && str[i + 1] != '_' && str[i + 1] != '\'' && str[i + 1] != '\"' && export == 0)
			return (0);
	if (str[i + 1] == '\'' && str[i + 1] != flag)
			return (0);
	if (str[i + 1] == '\"' && str[i + 1] != flag)
			return (0);
	return 1;	
}

int ft_search_char_equal_before_space_or_qoute(char *str, int i, int flag)
{
	if (i == 0)
		return (1);
	while (--i >= 0)
	{
		if (str[i] == '=')
			return (0);
		if (str[i] == ' ' && !flag)
			return (1);	
	}
	return (1);
}