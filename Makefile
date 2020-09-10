# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/12 18:43:36 by ndreadno          #+#    #+#              #
#    Updated: 2020/09/09 20:55:31 by ndreadno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
OBJ  = minishell.o parser.o ft_pork.o
LIB = -lft
INCLUDES = ./header.h
FLAGS = -g
all: $(NAME)
$(NAME):$(OBJ) $(LIB)
	gcc $(FLAGS) $(OBJ) -L. $(LIB) -o $(NAME)
%.o:%.c
	gcc $(FLAGS) -I $(INCLUDES) -c $< -o $@
$(LIB):
	@$(MAKE) -C libft/
	@mv libft/libft.a .
clean:
	/bin/rm -f $(OBJ)
	$(MAKE) -C libft clean
fclean:clean
	/bin/rm -f $(NAME)
	/bin/rm -f libft.a
re:fclean all
