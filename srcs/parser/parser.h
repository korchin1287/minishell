/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 16:28:59 by ndreadno          #+#    #+#             */
/*   Updated: 2020/09/17 11:36:35 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../../libft/libft.h"

int flag_exit;

typedef struct s_list_arg
{
	char **arg;
	int flag_redir_one;
	int flag_redir_two;
	int flag_redir_one_left;

	int flag_end;
	int flag_pipe;
	int flag_disable_char;
	int flag_disable_dollar;
	struct s_list_arg *next;
}t_list_arg;

typedef struct s_tmp_list
{
	char *str;
	int	flag;

	int flag_redir_one;
	int flag_redir_two;
	int flag_redir_one_left;
	int flag_redir_two_left;

	int flag_end;
	int flag_pipe;
	int flag_disable_char;
	int flag_disable_dollar;
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

	int flag_redir_one;
	int flag_redir_two;
	int flag_redir_one_left;

	int flag_end;
	int flag_pipe;
	int flag_disable_char;
	int flag_disable_dollar;
	int  arg;
	int count_arg;
	int error_arg;
	
}				t_parser;

typedef struct s_data
{
	t_parser parser;
	t_tmp_list *arg_list;
	t_list *env;
	t_list_arg **list;
	t_list *before_export;
}				t_data;

size_t		ft_strlen_2(const char *str, char *check);

int			ft_size_list(t_tmp_list *start);
int			ft_len_dollars(char *str, t_list *lst_before_export, t_list *list_env, int k);
int     	ft_check_arg(t_data *data, char *str, char c, int *k);
char		*ft_check_close_qoutes(t_data *data, char *str, int *i);
char		**make_map(t_tmp_list **map, int size);
void		ft_init(t_data *data);
void 		ft_clear_list(t_tmp_list **head);
void		ft_check_open_qoutes(t_data *data, char *str, int *i);
void		ft_add_end(t_tmp_list **start, t_tmp_list *new);
void		ft_parse_list(t_list_arg *list, t_list *lst_before_export, t_list *list_env);
char		*ft_change_dollar(t_data *data, char *str, char *dst);
int			ft_dollar(t_data *data, char *str, char *out, int *l);

t_list_arg	*ft_add_lst(t_data *data, t_tmp_list *tmp_list, char **str);
void 		ft_clear_lst(t_list_arg **head);
void		ft_add_lst_end(t_list_arg **start, t_list_arg *new);
char 		**ft_parse_line(t_list *lst_before_export, t_list *list_env, t_list_arg **list, char *line);

t_tmp_list	*ft_add(t_data *data, char *str);

void		ft_clear_list(t_tmp_list **head);
#endif