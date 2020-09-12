/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 16:28:59 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/11 22:32:08 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int flag_exit;
typedef struct s_echo
{
	int flag_n;
	int flag_V;
}t_echo;


typedef struct s_tmp_list
{
	char *str;
	char flag;
	struct s_tmp_list *next;
}t_tmp_list;

typedef struct s_parser
{
	int flag_open_quotes;
	int flag_close_quotes;
	int flag_single_quotes;
	int flag_double_quotes;
	int flag_single_quotes_count;
	int flag_double_quotes_count;
	char flag_arg;
	int  arg;
	int count_arg;
	
}				t_parser;

typedef struct s_data
{
	t_echo echo;
	t_parser parser;
	t_tmp_list *arg_list;
	char **env;
	int cd_flag;
	int echo_flag;
}				t_data;

void ft_init(t_data *data);
void ft_add_end(t_tmp_list **start, t_tmp_list *new);
t_tmp_list	*ft_add(t_data *data, char *str);
void ft_clear_list(t_tmp_list **head);
#endif