/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 13:07:07 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/15 11:48:30 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     ft_check_left_redirect(t_data *data, char *str, int l)
{
    int i;
    int k;

    i = 0;
    k = 0;
    while (str[l++] == '<')
        i++;
    k = l - 1;
    if (str[k] == ' ')
       k =  ft_space(str, k);
    if (i == 2)
        write (2, "minishell: syntax error near unexpected token `<'\n", 51);
    else if (i > 2)
        write (2, "minishell: syntax error near unexpected token `<<'\n", 52);
    else if (str[k] == '\0')
        write (2, "minishell: syntax error near unexpected token `newline'\n", 57);
    else if (str[k] == ';' || str[i] == ';')
        write (2, "minishell: syntax error near unexpected token `;'\n", 51);
    return (str[k] == ';' || str[i] == ';' || str[k] == '\0' || i != 1 ? 0 : i);
}

int     ft_check_end_command(t_data *data, char *str, int l)
{
    int i;
    int k;

    i = 0;
    k = 0;
    while(str[l++] == ';')
        i++;
    if (l == 2)
        write(2, "minishell: syntax error near unexpected token `;'\n", 51);
    if (i != 1)
        write(2, "minishell: syntax error near unexpected token `;;'\n", 52);
    return (i != 1 || l == 2 ? 0 : i);
    
}

int     ft_check_redirect(t_data *data, char *str, int l)
{
    int i;
    int k;

    i = 0;
    k = 0;
    while (str[l++] == '>')
        i++;
    k = l - 1;
    if (str[k] == ' ')
       k =  ft_space(str, k);
    if (i == 3)
        write (2, "minishell: syntax error near unexpected token `>'\n", 51);
    else if (i > 3)
        write (2, "minishell: syntax error near unexpected token `>>'\n", 52);
    else if (str[k] == '\0')
        write (2, "minishell: syntax error near unexpected token `newline'\n", 57);
    else if (str[k] == ';' || str[i] == ';')
        write (2, "minishell: syntax error near unexpected token `;'\n", 51);
    else if (str[k] == '<' || str[i] == '<')
        write (2, "minishell: syntax error near unexpected token `<'\n", 51);
    return (str[k] == '\0' || str[i] == ';' || str[k] == ';' ||  str[i] == '<' || str[k] == '<'|| i > 2 ? 0 : i);
}

int     ft_check_pipe(t_data *data, char *str, int l)
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
    if ((i > 1 && i <= 3) || j == 0)
        write (2, "minishell: syntax error near unexpected token `|'\n", 51);
    else if (i >= 2 && j == 0)
        write (2, "minishell: syntax error near unexpected token `||'\n", 52);
    else if (str[i] == ';' || str[k] == ';')
        write (2, "minishell: syntax error near unexpected token `;'\n", 51);
    else if (str[k] == '\0')
        write (2, "minishell: syntax error multiline command\n", 43);
     return (str[k] == '\0' || str[i] == ';' || str[k] == ';' || i > 1 || j == 0 ? 0 : i);
}

int     ft_check_arg(t_data *data, char *str, char c, int *k)
{
    int i;

    i = 0;
    if (str[*k] == '<')
    {
        if ((i = ft_check_left_redirect(data, str, *k)) == 1)
            data->parser.flag_redir_one_left = i == 1;
    }
    else if (str[*k] == '>')
    {
        if ((i = ft_check_redirect(data, str, *k)))
        {
            data->parser.flag_redir_one = i == 1 ? i : 0;
            data->parser.flag_redir_two = i == 2 ? 1 : 0;
        }
    }
    else if (str[*k] == ';')
    {
        if ((i = ft_check_end_command(data, str, *k)))
            data->parser.flag_end = 1;
    }
    else if (str[*k] == '|')
    {
        if ((i = ft_check_pipe(data, str, *k)))
            data->parser.flag_pipe = 1;
    }
    *k += i;
    return (i);
}