# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/12 18:43:36 by ndreadno          #+#    #+#              #
#    Updated: 2020/09/12 13:19:56 by ndreadno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = srcs/minishell.c srcs/parser.c srcs/ft_pork.c
OBJ  = srcs/minishell.o srcs/parser.o srcs/ft_pork.o
LIB = libft/libft.a
INCLUDES = ./srcs
FLAGS = -g 
all: $(NAME)

$(NAME):$(OBJ) $(LIB)
	gcc $(FLAGS) $(OBJ) $(LIB) -o $(NAME)
	/bin/rm -f test

%.o:%.c
	gcc $(FLAGS) -I $(INCLUDES) -c $< -o $@

ts:
	gcc -g srcs/*.c libft/*.c -o test
	/bin/rm -f minishell
$(LIB):
	@$(MAKE) -C libft/

clean:
	/bin/rm -f $(OBJ)
	$(MAKE) -C libft clean

fclean:clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(LIB)
re:fclean all
