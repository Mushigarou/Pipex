# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 04:43:36 by mfouadi           #+#    #+#              #
#    Updated: 2023/02/22 10:13:40 by mfouadi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bin/pipex

CC = cc

CFLAGS = -Wall -Werror -Wextra

M_SRC = pipex.c main.c utils.c

OBJ_M_SRC = $(M_SRC:.c=.o)

OBJ_M_SRC_PATH = $(addprefix obj/, $(OBJ_M_SRC))

HEADER = include/pipex.h

LIBFT_ARCHIVE = Libft/libft.a

RM = rm -rf

all : $(NAME)

$(NAME) : dir lib $(OBJ_M_SRC_PATH)
	$(CC) $(CFLAGS) $(OBJ_M_SRC_PATH) $(LIBFT_ARCHIVE) -o $(NAME)

obj/%.o : mandatory_src/%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I include -I Libft

dir :
	mkdir -p obj bin

lib :
	make -C Libft

re_lib :
	make fclean -C Libft

debug :
	make
	$(CC) $(CFLAGS) -fsanitize=address $(OBJ_M_SRC_PATH) $(LIBFT_ARCHIVE) -o $(NAME)

clean :
	make clean -C Libft
	$(RM) obj

fclean : clean re_lib
	$(RM) $(LIBFT_ARCHIVE) bin

re : re_lib fclean all

.PHONY : all $(NAME) clean fclean re lib dir re_lib debug
.DEFAULT_GOAL := all
