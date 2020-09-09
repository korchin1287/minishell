/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 12:47:52 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/09 14:00:14 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void ft_clear_list(t_list **head)
{
	t_list *tmp;

	
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->str);
		tmp->str = NULL;
		free(tmp);
		tmp = NULL;
		
	}
	
}
t_list	*ft_add(t_minshl *shell, char *str)
{
	t_list *new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
	{
		// vars->parse.erorrs.flag_malloc_error = 1;
		// ft_errors(vars);
	}
	new->str = str;
	new->next = NULL;
	return (new);
}

void		ft_add_end(t_list **start, t_list *new)
{
	t_list *tmp;

	tmp = *start;
	if (tmp == NULL)
	{
		(*start) = new;
		return;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
int ft_size_list(t_list *start)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = start;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return i;
}

void ft_quotes_null(t_minshl *shell)
{
	shell->parser.flag_close_quotes = 0;
	shell->parser.flag_open_quotes = 0;
	shell->parser.flag_single_quotes = 0;
	shell->parser.flag_double_quotes = 0;
}

void ft_init(t_minshl *shell)
{
	shell->parser.flag_close_quotes = 0;
	shell->parser.flag_open_quotes = 0;
	shell->parser.flag_single_quotes = 0;
	shell->parser.flag_double_quotes = 0;
	shell->echo.flag_n = 0;
	shell->arg_list = NULL;
	shell->parser.count_arg = 0;
	shell->echo_flag = 0;
}

char *ft_qoutes(t_minshl *shell, char *str, int *i)
{
	char *s;
	int k;
	char c = str[*i];
	char q;

	k = *i;
	while (str[*i] != '\0')
	{
		if (str[*i] == '\'' && shell->parser.flag_single_quotes == 1)
		{
			shell->parser.flag_close_quotes = 1;
			break;
		}
		if (str[*i] == '\"' && shell->parser.flag_double_quotes == 1)
		{
			shell->parser.flag_close_quotes = 1;
			break;
		}
		(*i)++;
	}
	if (shell->parser.flag_close_quotes != 1)
		return NULL;
	q = str[*i];
	s = ft_substr(str, k , *i - k);
	*i = ft_space(str, *i + 1);
	return (s);
}
char *ft_string(t_minshl *shell, char *str, int *i)
{
	int k;
	char *s;

	k = *i;
	while (str[*i])
	{
		if (str[*i] == ' ')
		{
			break;	
		}
		if (str[*i] == '\'')
		{
			exit(1);
		}
		if (str[*i] == '\"')
		{
			exit(1);
		}
		(*i)++;
	}
	s = ft_substr(str, k, *i - k);
	*i = ft_space(str, *i);
	return s;
	
}
void ft_check_command(t_minshl *shell, t_list *(*command))
{
	t_list *tmp;
	int i;

	i = 1;
	tmp = (*command);
	if (ft_strcmp((*command)->str, "cd") == 0)
	{
		if (!(*command)->next)
			ft_cd(shell, (*command)->str);
		else
			ft_cd(shell, (*command)->next->str);
		
	}
	if (ft_strcmp((*command)->str, "pwd") == 0)
		ft_pwd(shell);
	if (ft_strcmp((*command)->str, "env") == 0)
		ft_env(shell);
	if (ft_strcmp((*command)->str, "echo") == 0)
	{
		if (ft_strcmp((*command)->next->str, "-n") == 0)
			shell->echo_flag = 1;
		tmp = shell->echo_flag == 1 ? (*command)->next->next : ((*command))->next;
		while (tmp)
		{
			if (!tmp->next)
				i = 0;
			ft_echo(shell, tmp->str, i);
			tmp = tmp->next;
			
		}
		
	}
	ft_clear_list(command);	
}
void ft_parse_line(t_minshl *shell, char *line)
{
	char *str;
	int i;

	i = 0;
	str = ft_strtrim(line, " \t");
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			shell->parser.flag_single_quotes = 1;
		}
		if (str[i] == '\"')
		{
			shell->parser.flag_double_quotes = 1;
		}
		if (shell->parser.flag_single_quotes != 1 && shell->parser.flag_double_quotes != 1)
		{
			ft_add_end(&shell->arg_list, ft_add(shell, ft_string(shell, str, &i)));
			if (str[i])
			{
				char c = str[i];
			}
		}
		if (shell->parser.flag_single_quotes == 1 || shell->parser.flag_double_quotes == 1)
		{
			i++;
			ft_add_end(&shell->arg_list, ft_add(shell, ft_qoutes(shell, str, &i)));
			ft_quotes_null(shell);
		}
	}
	shell->parser.count_arg = ft_size_list(shell->arg_list->next);
	ft_check_command(shell, &shell->arg_list);
}