/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 16:28:59 by ndreadno          #+#    #+#             */
/*   Updated: 2020/10/03 14:14:51 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../../libft/libft.h"

typedef struct	s_list_arg
{
	char				**arg;
	int					flag_redir_one;
	int					flag_redir_two;
	int					flag_redir_one_left;
	int					flag_end;
	int					flag_pipe;
	int					flag_disable_char;
	int					flag_disable_dollar;
	struct s_list_arg	*next;
	struct s_list_arg	*back;
}				t_list_arg;

typedef struct	s_tmp_list
{
	char				*str;
	int					flag;
	int					flag_redir_one;
	int					flag_redir_two;
	int					flag_redir_one_left;
	int					flag_redir_two_left;
	int					flag_end;
	int					flag_pipe;
	int					flag_disable_char;
	int					flag_disable_dollar;
	struct s_tmp_list	*next;
}				t_tmp_list;

typedef struct	s_parser
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
	int arg;
	int count_arg;
	int error_arg;
}				t_parser;

typedef struct	s_data
{
	t_parser	parser;
	t_tmp_list	*arg_list;
	t_list		*env;
	t_list_arg	**list;
	t_list		*before_export;
	char		*out;
}				t_data;

int				ft_check_char_qual(t_data *data, char *str, int k, char flag);
size_t			ft_count_dollar(const char *str);
int				ft_check_redirect(char *str, int l);
int				ft_check_left_redirect(char *str, int l);
int				ft_check_cmd(t_tmp_list *list);
int				ft_size_list(t_tmp_list *start);
int				ft_parse_redirect_pipe(t_data *data, char *str, int len, int i);
int				ft_condition_check(char *str, int *i, int flag_cond);
int				ft_condition_check2(char *str, int i, char c, int flag);
int				ft_len_dollars(char *str, t_list *lst_bfe,
					t_list *list_env, int k);
int				ft_check_arg(t_data *data, char *str, int *k);
char			*ft_check_close_qoutes(t_data *data, char *str, int *i);
char			**make_map(t_tmp_list **map, int size);
void			ft_flag_null(t_data *data);
void			ft_qoutes_null(t_data *data);
void			ft_clear_list(t_tmp_list **head);
void			ft_check_open_qoutes(t_data *data, char *str, int *i);
void			ft_add_end(t_tmp_list **start, t_tmp_list *new);
void			ft_parse_arg_loop_list(t_data *data, char *str, int *i);
char			*ft_change_dollar(t_data *data, char *str, char *dst);
int				ft_dollar(t_data *data, char *str, char *out, int *l);
int				ft_check_char_qual(t_data *data, char *str, int k, char flag);
int				ft_check_cmd(t_tmp_list *list);
int				ft_search_char_equal_before_space_or_qoute(char *str,
				int i, int flag);
int				ft_len_arg_list(t_data *data, char *str, int *i);
int				ft_check_redirect(char *str, int l);
int				ft_len_qoutes_list(t_data *data, char *str, char c, int *i);
t_list_arg		*ft_add_lst(t_data *data, char **str);
void			ft_clear_lst(t_list_arg **head);
void			ft_add_lst_end(t_list_arg **start, t_list_arg *new);
void			ft_parse_arg_loop_list(t_data *data, char *str, int *i);
char			*ft_check_doll(char *str, t_list *lst, int count);
char			*ft_until_the_quote_is_closed(t_data *data, char *str, int *i);
t_tmp_list		*ft_add(t_data *data, char *str);
void			ft_clear_list(t_tmp_list **head);

#endif
