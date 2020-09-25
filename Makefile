# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/12 18:43:36 by ndreadno          #+#    #+#              #
#    Updated: 2020/09/24 19:12:10 by ndreadno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = srcs/minishell/ft_pork.c srcs/minishell/minishell.c \
	srcs/minishell/ft_add_list_before_export.c srcs/minishell/ft_command_export.c \
	srcs/minishell/ft_command_cd.c srcs/minishell/ft_command_env.c \
	srcs/minishell/ft_command_echo.c srcs/minishell/ft_command_unset.c \
	srcs/minishell/ft_command_bash.c srcs/minishell/signal.c srcs/minishell/ft_read_info.c \
	srcs/minishell/ft_make_with_pipe.c srcs/minishell/ft_execve.c
	

SRCS_PARS = srcs/parser/parser.c srcs/parser/parser2.c srcs/parser/list.c \
	srcs/parser/open_close_qoutes.c srcs/parser/check_arg.c \
	srcs/parser/dollar.c srcs/parser/env_dollar.c
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
