# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/01 22:17:03 by mohammoh          #+#    #+#              #
#    Updated: 2024/01/26 13:23:21 by mabdelsa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SOURCES = \
		srcs/main.c srcs/parsing/ft_split.c srcs/parsing/ft_split2.c srcs/parsing/extra.c srcs/parsing/error.c \
		srcs/parsing/extra2.c srcs/parsing/file_type.c srcs/parsing/files_num_in_each_part.c \
		srcs/parsing/load_files_names.c srcs/parsing/num_of_chars_in_each_file.c srcs/parsing/qut.c \
		srcs/parsing/remove_qut_from_cmds.c srcs/parsing/trim_all.c srcs/parsing/dollar.c srcs/parsing/dollar2.c\
		srcs/parsing/dollar3.c srcs/parsing/extra3.c srcs/parsing/free.c\
		srcs/execution/builtins/echo_built_in.c srcs/execution/builtins/pwd_built_in.c srcs/execution/builtins/exit_built_in.c \
		srcs/execution/builtins/env_built_in.c srcs/execution/builtins/dict_utils.c srcs/execution/builtins/export_built_in.c \
		srcs/execution/builtins/unset_built_in.c srcs/execution/builtins/cd_built_in.c srcs/execution/builtins/sort_dictionary.c \
		srcs/execution/builtins/execute_built_ins.c srcs/execution/builtins/args_error_msgs.c srcs/execution/handle_out_file.c \
		srcs/execution/handle_in_file.c srcs/execution/check_func_path_acess.c srcs/execution/create_children.c \
		srcs/execution/signals.c srcs/execution/search_dictionary.c srcs/execution/builtins/args_error_msgs2.c \
		srcs/execution/dup2_functions.c srcs/execution/open_pipes.c srcs/execution/open_all_input_files.c \
		srcs/execution/heredoc.c
		
OBJECTS = $(SOURCES:%.c=%.o)

LIBFTBF = ./includes/libft/libft.a
LIBFT_P = ./includes/libft
LIBFT_AR = ./includes/libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBSR = -L$(HOME)/local/lib -lreadline -lncurses


all: $(NAME)

$(NAME): $(OBJECTS)
	$(MAKE) -C $(LIBFT_P)
	echo ${OBJECTS}
	$(CC) $(CFLAGS) $(SOURCES) $(LIBFT_AR) -o $(NAME) -I/Users/mabdelsa/local/include/readline/ $(LIBSR)
	install_name_tool -change /usr/local/lib/libreadline.8.dylib $(HOME)/local/lib/libreadline.8.dylib $(NAME)
	

%.o: %.c
	${CC} ${CFLAGS} -c $< -I/Users/mabdelsa/local/include/readline/ -o $@

clean:
	$(MAKE) clean -C $(LIBFT_P)
	/bin/rm -f $(OBJECTS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_P)
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re valgrind
