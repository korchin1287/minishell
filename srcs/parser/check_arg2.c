/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 14:11:35 by ndreadno          #+#    #+#             */
/*   Updated: 2020/10/03 15:15:49 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_return(char *str, int i, int k)
{
	if (str[k] == '\0' || str[i] == ';' || str[k] == ';' || str[i] == '<' ||
		((str[i] == '|' || str[k] == '|') && (i > 1 || str[i + 1] == '\0'))
			|| str[k] == '<' || i > 2)
		return (0);
	return (i);
}

int		ft_check_left_redirect(char *str, int l)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (str[l++] == '<')
		i++;
	k = l - 1;
	if (str[k] == ' ')
		k = ft_space(str, k);
	if (i == 2)
		write(2, "minishell: syntax error near unexpected token `<'\n", 51);
	else if (i > 2)
		write(2, "minishell: syntax error near unexpected token `<<'\n", 52);
	else if (str[k] == '\0')
		write(2, "minishell: syntax error near unexpected token `newline'\n",
		57);
	else if (str[k] == ';' || str[i] == ';')
		write(2, "minishell: syntax error near unexpected token `;'\n", 51);
	return (str[k] == ';' || str[i] == ';' ||
		str[k] == '\0' || i != 1 ? 0 : i);
}

int			ft_check_redirect(char *str, int l)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (str[l++] == '>')
		i++;
	k = l - 1;
	if (str[k] == ' ')
		k = ft_space(str, k);
	if (i == 3)
		write(2, "minishell: syntax error near unexpected token `>'\n", 51);
	else if (i > 3)
		write(2, "minishell: syntax error near unexpected token `>>'\n", 52);
	else if (str[k] == '\0' || (str[i] == '|' && str[i + 1] == '\0'))
		write(2, "minishell: syntax error near unexpected token `newline'\n",
			57);
	else if (str[k] == ';' || str[i] == ';')
		write(2, "minishell: syntax error near unexpected token `;'\n", 51);
	else if (str[k] == '<' || str[i] == '<')
		write(2, "minishell: syntax error near unexpected token `<'\n", 51);
	else if ((str[k] == '|' || str[i] == '|') && i > 1)
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
	return (ft_return(str, i, k));
}
