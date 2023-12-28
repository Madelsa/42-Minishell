# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/22 16:27:40 by aalkaisi          #+#    #+#              #
#    Updated: 2023/12/28 16:40:27 by mabdelsa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=	main.c ft_splitt.c extra.c echo_built_in.c pwd_built_in.c exit_built_in.c env_built_in.c dict_utils.c \
		export_built_in.c unset_built_in.c cd_built_in.c
		
NAME = minishell
AR = ar rs
RM = rm -f
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_P = ./libft/
LIBFT_AR = ./libft/libft.a

OBJS = $(SRC:.c=.o)
OBJS_B = $(SRC_B:.c=.o)

all: $(NAME)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_AR)
	$(CC) $(OBJS) $(LIBFT_AR) -o $(NAME) -lreadline

$(LIBFT_AR):
	make -C $(LIBFT_P)

clean:
	make -C $(LIBFT_P) clean
	@$(RM) $(OBJS)

fclean: clean
	make -C $(LIBFT_P) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
