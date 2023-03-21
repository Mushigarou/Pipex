# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 05:06:00 by mfouadi           #+#    #+#              #
#    Updated: 2023/03/19 08:44:04 by mfouadi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------------------------------------------------------------------------------
# .c Files, and list of .o Files, 
#-------------------------------------------------------------------------------

# push_swap directory
ROOTDIR := .

# obj folder where .o files will be placed
OBJDIR := obj

# directory of headers files
INCDIR := inc

# Data structures
SRC_DS_SLL := dataStructures/singlyLinkedList/ft_lstadd_back.c \
              dataStructures/singlyLinkedList/ft_lstadd_front.c \
              dataStructures/singlyLinkedList/ft_lstclear.c \
              dataStructures/singlyLinkedList/ft_lstdelone.c \
              dataStructures/singlyLinkedList/ft_lstiter.c \
              dataStructures/singlyLinkedList/ft_lstlast.c \
              dataStructures/singlyLinkedList/ft_lstmap.c \
              dataStructures/singlyLinkedList/ft_lstnew.c \
              dataStructures/singlyLinkedList/ft_lstsize.c \
\
              dataStructures/doublyLinkedList/pushnode.c \
              dataStructures/doublyLinkedList/new_node.c \
              dataStructures/doublyLinkedList/last_node.c \
              dataStructures/doublyLinkedList/addback_node.c \
              dataStructures/doublyLinkedList/addafter_node.c \
              dataStructures/doublyLinkedList/addbefore_node.c \
              dataStructures/doublyLinkedList/clear_nodes.c

# Character functions
SRC_FT_IS := ft_is/ft_isalnum.c \
             ft_is/ft_isalpha.c \
             ft_is/ft_isascii.c \
             ft_is/ft_isdigit.c \
             ft_is/ft_isprint.c \
             ft_is/ft_tolower.c \
             ft_is/ft_toupper.c

# Get Next Line
SRC_GNL   := getNextLine/get_next_line.c \
             getNextLine/get_next_line_utils.c

# Memory functions
SRC_MEM   := malloc/ft_calloc.c \
             mem/ft_bzero.c \
             mem/ft_memchr.c \
             mem/ft_memcmp.c \
             mem/ft_memcpy.c \
             mem/ft_memmove.c \
             mem/ft_memset.c

# Printf
SRC_PRINTF := printf/ft_printf.c \
              printf/utils/conv_hex.c \
              printf/utils/printf_putchar_fd.c \
              printf/utils/printf_putnbr_fd.c \
              printf/utils/printf_putstr_fd.c \
              printf/utils/printf_putunbr_fd.c \
              printf/utils/wr_address.c

# Random
SRC_RAND  := random/ft_rand.c

# String functions
SRC_STR   := str/conversion/ft_atoi.c \
             str/conversion/ft_itoa.c \
             str/ft_split.c \
             str/ft_strchr.c \
             str/ft_strdup.c \
             str/ft_striteri.c \
             str/ft_strjoin.c \
             str/ft_strlcat.c \
             str/ft_strlcpy.c \
             str/ft_strlen.c \
             str/ft_strmapi.c \
             str/ft_strncmp.c \
             str/ft_strnstr.c \
             str/ft_strrchr.c \
             str/ft_strtrim.c \
             str/ft_substr.c \
             str/put/ft_putchar_fd.c \
             str/put/ft_putendl_fd.c \
             str/put/ft_putnbr_fd.c \
             str/put/ft_putstr_fd.c

# Sorting Algorithms
SRC_SORT := sortingAlgo/bubble_sort/bubble_sort.c \
			sortingAlgo/bubble_sort/opt_bubble_sort.c \
			sortingAlgo/insertion_sort.c \
			sortingAlgo/merge_sort.c \
			sortingAlgo/selection_sort.c \

# Combine all sources
SRC  := $(SRC_DS_SLL) $(SRC_FT_IS) $(SRC_GNL) \
		$(SRC_MEM) $(SRC_PRINTF) $(SRC_RAND) $(SRC_STR) \
		$(SRC_SORT)

# Headers files
HEADERS  := ./inc/ft_printf.h \
			./inc/get_next_line.h \
			./inc/libft.h \
			./inc/sorting.h

# ('pattern substitution') patsubst (pattern, replacement string, list of names) 
# List of object files to be generated
OBJ := $(patsubst %, $(OBJDIR)/%, $(SRC:.c=.o))

#-------------------------------------------------------------------------------
# Variables
#-------------------------------------------------------------------------------

# Ultimate Goal
NAME := libft.a

# Flags used in compilation
CFLAGS := -Werror -Wextra -Wall -I$(INCDIR)

# Command used to rm files and obj directory
RM := /bin/rm -rf

# Used for animation
FILES_COMPILED = 0
TOTAL_FILES = $(shell find $(ROOTDIR) -type f -name "*.c" | wc -l)

#-------------------------------------------------------------------------------
# Terminal ANSI colors
#-------------------------------------------------------------------------------
HBLK = '\e[1;90m'
HRED = '\e[1;91m'
HGRN = '\e[1;92m'
HYEL = '\e[1;93m'
HBLU = '\e[1;94m'
HMAG = '\e[1;95m'
HCYN = '\e[1;96m'
HWHT = '\e[1;97m'
NC ='\033[0m'

#-------------------------------------------------------------------------------
# Main dependencies
#-------------------------------------------------------------------------------

# Target 'all' depends on static library ($(NAME))
all : $(NAME)

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)

# $(eval ...) is used to dynamically generate makefile rules.
#	- Output of the command is interpreted as makefile code
#	- Generated code is added to the Makefile and executed when the makefile run

# $(shell ...) is used to capture the value of the output of shell and stores it 
#	  	in a make variable
#	- i.e. $(shell TEST = $(echo "hello"))
$(OBJDIR)/%.o : %.c $(HEADERS)
	$(eval FILES_COMPILED = $(shell echo "$(FILES_COMPILED) + 1" | bc ))
	@ printf ${HBLK}"  Compiling ▻"${HBLK}" [%-20s] "${HBLK} $(notdir $@)
	@ echo "$(FILES_COMPILED) * 100 / $(TOTAL_FILES)" | bc | tr -d '\n'
	@ printf "%% \r"${NC}
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) -c $< -o $@

x :
	@echo "$(SRC) \n\n"
	@echo $(OBJ)
#-------------------------------------------------------------------------------
# Deletion
#-------------------------------------------------------------------------------

# Deletes object files
clean :
	$(RM) $(OBJDIR)

# Deletes libft.a
fclean : clean
	$(RM) $(NAME)

# re-compile all .c files
re : fclean all

#-------------------------------------------------------------------------------
# Special Built-in Target Names
#-------------------------------------------------------------------------------

# Words that do not represent files of the project
.Phony : all clean fclean re

# Prevents output of these targets from being printed
.SILENT : bonus $(NAME) clean fclean re

# Makes 'all' the default target
.DEFAULT_GOAL := all
