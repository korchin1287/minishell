# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/03 16:13:20 by ndreadno          #+#    #+#              #
#    Updated: 2020/10/04 17:21:06 by nofloren         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = srcs/minishell/ft_pork.c srcs/minishell/minishell.c\
	srcs/minishell/ft_add_list_before_export.c srcs/minishell/ft_command_export.c\
	srcs/minishell/ft_command_cd.c srcs/minishell/ft_command_env.c\
	srcs/minishell/ft_command_echo.c srcs/minishell/ft_command_unset.c\
	srcs/minishell/ft_command_bash.c srcs/minishell/signal.c srcs/minishell/ft_read_info.c\
	srcs/minishell/ft_make_with_pipe.c srcs/minishell/ft_execve.c srcs/minishell/ft_make_with_left_redir.c\
	srcs/minishell/ft_make_with_redir.c srcs/minishell/ft_command_bash_help1.c \
	srcs/minishell/ft_make_with_redir_2.c srcs/minishell/ft_command_export_2.c \
	srcs/minishell/ft_list_create.c srcs/minishell/ft_sort_mass.c \
	srcs/minishell/ft_command_exit.c srcs/minishell/ft_minishell_help.c \
	srcs/minishell/ft_minishell_help_2.c srcs/minishell/ft_getcwd.c \
	srcs/minishell/ft_free_str.c srcs/minishell/ft_command_pwd.c \
	srcs/minishell/ft_make_with_redir_help3.c
	

SRCS_PARS = srcs/parser/parser.c srcs/parser/parser2.c srcs/parser/list.c\
	srcs/parser/list2.c srcs/parser/open_close_qoutes.c srcs/parser/check_arg.c\
	srcs/parser/dollar.c srcs/parser/env_dollar.c srcs/parser/ft_until_the_quote_is_closed.c\
	srcs/parser/init_and_null_parser1.c srcs/parser/condition_check.c srcs/parser/len_arg.c\
	srcs/parser/parse_redirect_and_pipe.c srcs/parser/char_qual.c srcs/parser/len_arg_list_line.c\
	srcs/parser/condition_check2.c srcs/parser/check_arg2.c srcs/parser/parser2_loop.c

OBJ = $(SRCS:.c=.o)
OBJ_PARS = $(SRCS_PARS:.c=.o)
#OBJ  = srcs/minishell.o srcs/parser.o srcs/ft_pork.o
LIB = libft/libft.a
INCLUDES = ./srcs
FLAGS = -g 
all: $(NAME)

$(NAME):$(OBJ) $(OBJ_PARS) $(LIB)
	gcc $(FLAGS) $(OBJ) $(OBJ_PARS) $(LIB) -o $(NAME)

%.o:%.c
	gcc $(FLAGS) -I $(INCLUDES) -c $< -o $@

ts:
	gcc -g srcs/minishell/*.c srcs/parser/*.c libft/*.c -o minishell
$(LIB):
	@$(MAKE) -C libft/

clean:
	/bin/rm -f $(OBJ) $(OBJ_PARS)
	$(MAKE) -C libft clean

fclean:clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(LIB)
re:fclean all
