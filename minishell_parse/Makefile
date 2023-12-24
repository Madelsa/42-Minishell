# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/22 16:27:40 by aalkaisi          #+#    #+#              #
#    Updated: 2023/12/24 14:57:43 by mabdelsa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.c ft_split.c extra.c echo_built_in.c pwd_built_in.c exit_built_in.c ft_strncmp.c ft_putstr_fd.c ft_isdigit.c

OBJ = $(SRC:.c=.o)

CC = cc

NAME = minishell

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@
	
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline

clean:
	@rm -f $(OBJ)
	
fclean: clean
	@rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re