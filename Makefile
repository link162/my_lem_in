# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/21 14:55:38 by ybuhai            #+#    #+#              #
#    Updated: 2019/03/18 16:07:53 by ybuhai           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	lem-in

LIB			=	libftprintf/
LIB_N		=	libftprintf.a

SRC_D		=	src/
SRC			=	$(SRC_D)main.c \
				$(SRC_D)add_pipes_to_rooms.c \
				$(SRC_D)read_data.c \
				$(SRC_D)error_case.c \
				$(SRC_D)check_pipe.c \
				$(SRC_D)convert_to_arr.c \
				$(SRC_D)find_ways.c \
				$(SRC_D)check_room_in_way.c \
				$(SRC_D)add_way_in_struct.c \
				$(SRC_D)set_index.c \
				$(SRC_D)algorithm_big.c \
				$(SRC_D)print_lem.c \

OBJ_D		=	obj/
OBJ			=	$(addprefix $(OBJ_D), $(SRC:.c=.o))

INCLUDE		=	-I includes/
CFLAGS		=	-Wall -Wextra -Werror -Ofast
C			=	gcc

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB)
	@$(C) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)$(LIB_N) $(INCLUDE)

$(OBJ): $(OBJ_D)

$(OBJ_D):
	@mkdir -p $(OBJ_D)$(SRC_D)

$(OBJ_D)%.o: %.c
	@$(C) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	@make clean -C $(LIB)
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIB)
	@rm -f $(NAME)
	@rm -rf $(OBJ_D)

re: fclean all

.PHONY: all clean fclean re
