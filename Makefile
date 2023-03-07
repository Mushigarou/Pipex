# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 04:43:36 by mfouadi           #+#    #+#              #
#    Updated: 2023/03/06 05:06:35 by mfouadi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAGS = -Wall -Werror -Wextra

M_SRC = pipex.c main.c utils.c
B_SRC = pipex_bonus.c main_bonus.c utils_bonus.c exec_bonus.c

OBJ_M_SRC = $(M_SRC:.c=.o)
OBJ_B_SRC = $(B_SRC:.c=.o)

OBJ_M_SRC_PATH = $(addprefix obj/, $(OBJ_M_SRC))
OBJ_B_SRC_PATH = $(addprefix obj/, $(OBJ_B_SRC))

HEADER = include/pipex.h

LIBFT_ARCHIVE = Libft/libft.a

RM = rm -rf

all : $(NAME)

$(NAME) : dir lib $(OBJ_M_SRC_PATH)
	$(CC) $(CFLAGS) $(OBJ_M_SRC_PATH) $(LIBFT_ARCHIVE) -o $(NAME)

obj/%.o : mandatory_src/%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I include -I Libft

dir :
	mkdir -p obj

lib :
	make -C Libft

re_lib :
	make fclean -C Libft

debug :
	make
	$(CC) $(CFLAGS) -fsanitize=address $(OBJ_M_SRC_PATH) $(LIBFT_ARCHIVE) -o $(NAME)

debug_b : lib dir $(OBJ_B_SRC_PATH)
	make
	$(CC) $(CFLAGS) -fsanitize=address $(OBJ_B_SRC_PATH) $(LIBFT_ARCHIVE) -o $(NAME)

bonus : dir lib $(OBJ_B_SRC_PATH)
	$(CC) $(CFLAGS) $(OBJ_B_SRC_PATH) $(LIBFT_ARCHIVE) -o $(NAME)

obj/%.o : bonus_src/%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I include -I Libft

clean :
	make clean -C Libft
	$(RM) obj

fclean : clean re_lib
	$(RM) $(LIBFT_ARCHIVE) bin

re : re_lib fclean all

.PHONY : all $(NAME) clean fclean re lib dir re_lib debug bonus
.DEFAULT_GOAL := all
