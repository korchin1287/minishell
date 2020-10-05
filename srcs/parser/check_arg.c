/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 13:07:07 by ndreadno          #+#    #+#             */
/*   Updated: 2020/10/05 16:21:56 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_check_end_command(char *str, int l)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (str[l++] == ';')
		i++;
	k = l - 1;
	while (str[k] == ' ')
		k++;
	if (i != 1)
		write(2, "minishell: syntax error near unexpected token `;;'\n", 52);
	else if (i == 2 || str[k] == ';' || str[k] == '\0')
		write(2, "minishell: syntax error near unexpected token `;'\n", 51);
	return (i != 1 || l == 2 || str[k] == ';' || str[k] == '\0' ? 0 : i);
}

int		ft_check_pipe(char *str, int l)
{
	int i;
	int k;
	int j;

	i = 0;
	k = 0;
	j = l;
	while (str[l++] == '|')
		i++;
	k = l - 1;
	if (str[k] == ' ')
		k = ft_space(str, k);
	if ((i > 1 && i <= 3) || j == 0 || str[k] == '|')
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
	else if (i >= 2 && j == 0)
		write(2, "minishell: syntax error near unexpected token `||'\n", 52);
	else if (str[i] == ';' || str[k] == ';')
		write(2, "minishell: syntax error near unexpected token `;'\n", 51);
	else if (str[k] == '\0')
		write(2, "minishell: syntax error multiline command\n", 43);
	return (str[k] == '\0' || str[i] == ';' || str[k] == ';'
			|| i > 1 || j == 0 || str[k] == '|' ? 0 : i);
}

int		ft_check_arg(t_data *data, char *str, int *k)
{
	int i;

	i = 0;
	if (str[*k] == '<')
		if ((i = ft_check_left_redirect(str, *k)) == 1)
			data->parser.flag_redir_one_left = i == 1;
	if (str[*k] == '>')
		if ((i = ft_check_redirect(str, *k)))
		{
			data->parser.flag_redir_one = i == 1 ? i : 0;
			data->parser.flag_redir_two = i == 2 ? 1 : 0;
		}
	if (str[*k] == ';')
		if ((i = ft_check_end_command(str, *k)))
			data->parser.flag_end = 1;
	if (str[*k] == '|')
		if ((i = ft_check_pipe(str, *k)))
			data->parser.flag_pipe = 1;
	*k += i;
	return (i);
}
