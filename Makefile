# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/01 22:17:03 by mohammoh          #+#    #+#              #
#    Updated: 2024/01/03 16:00:30 by mabdelsa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 	srcs/main.c srcs/parsing/main.c srcs/parsing/ft_split.c srcs/parsing/extra.c srcs/parsing/error.c \
		srcs/parsing/extra2.c srcs/parsing/file_type.c srcs/parsing/files_num_in_each_part.c \
		srcs/parsing/load_files_names.c srcs/parsing/num_of_chars_in_each_file.c srcs/parsing/qut.c \
		srcs/parsing/remove_qut_from_cmds.c srcs/parsing/trim_all.c \
		srcs/execution/builtins/echo_built_in.c srcs/execution/builtins/pwd_built_in.c srcs/execution/builtins/exit_built_in.c \
		srcs/execution/builtins/env_built_in.c srcs/execution/builtins/dict_utils.c srcs/execution/builtins/export_built_in.c \
		srcs/execution/builtins/unset_built_in.c srcs/execution/builtins/cd_built_in.c srcs/execution/builtins/sort_dictionary.c \
		srcs/execution/builtins/execute_built_ins.c srcs/execution/builtins/args_error_msgs.c srcs/execution/handle_out_file.c \


NAME = minishell
AR = ar rs
RM = rm -f
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_P = includes/libft/
LIBFT_AR = includes/libft/libft.a

OBJS = $(SRC:.c=.o)

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
