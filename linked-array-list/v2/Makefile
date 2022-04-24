# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minhojan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 19:35:49 by minhojan          #+#    #+#              #
#    Updated: 2022/03/21 15:35:03 by minhojan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SRC = ./arraylist.c ./linkedlist.c
#BONUS
OBJ = $(SRC:.c=.o)
#B_OBJ = $(BONUS:.c=.o)
CFLAGS += -Wall -Wextra -Werror -I./include
NAME = list.a
#ifdef q
#	T = $(OBJ) $(B_OBJ)
#else
#	T = $(OBJ)
#endif
#bonus
.PHONY: all clean fclean re
all : $(NAME)
$(NAME): $(OBJ) #$(T)
	ar -rcs $@ $^
#bonus:
#	@make q=1 all
clean: #$(B_OBJ)
	@rm -f $(OBJ)
fclean: clean
	@rm -rf $(NAME)
re: fclean all
