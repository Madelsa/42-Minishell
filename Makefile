# # **************************************************************************** #
# #                                                                              #
# #                                                         :::      ::::::::    #
# #    Makefile                                           :+:      :+:    :+:    #
# #                                                     +:+ +:+         +:+      #
# #    By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+         #
# #                                                 +#+#+#+#+#+   +#+            #
# #    Created: 2023/12/01 22:17:03 by mohammoh          #+#    #+#              #
# #    Updated: 2024/01/04 20:18:20 by mabdelsa         ###   ########.fr        #
# #                                                                              #
# # **************************************************************************** #

# SRC = 	srcs/main.c srcs/parsing/main1.c srcs/parsing/ft_split.c srcs/parsing/extra.c srcs/parsing/error.c \
# 		srcs/parsing/extra2.c srcs/parsing/file_type.c srcs/parsing/files_num_in_each_part.c \
# 		srcs/parsing/load_files_names.c srcs/parsing/num_of_chars_in_each_file.c srcs/parsing/qut.c \
# 		srcs/parsing/remove_qut_from_cmds.c srcs/parsing/trim_all.c \
# 		srcs/execution/builtins/echo_built_in.c srcs/execution/builtins/pwd_built_in.c srcs/execution/builtins/exit_built_in.c \
# 		srcs/execution/builtins/env_built_in.c srcs/execution/builtins/dict_utils.c srcs/execution/builtins/export_built_in.c \
# 		srcs/execution/builtins/unset_built_in.c srcs/execution/builtins/cd_built_in.c srcs/execution/builtins/sort_dictionary.c \
# 		srcs/execution/builtins/execute_built_ins.c srcs/execution/builtins/args_error_msgs.c srcs/execution/handle_out_file.c \
# 		srcs/execution/handle_in_file.c srcs/execution/check_func_path_acess.c

# NAME = minishell
# AR = ar rs
# RM = rm -f
# CC = cc
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address

# LIBFT_P = includes/libft/
# LIBFT_AR = includes/libft/libft.a

# OBJS = $(SRC:.c=.o)

# all: $(NAME)

# $(OBJS): %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(NAME): $(OBJS) $(LIBFT_AR)
# 	$(CC) $(LIBFT_AR) $(OBJS) -o $(NAME) -lreadline

# $(LIBFT_AR):
# 	make -C $(LIBFT_P)

# clean:
# 	make -C $(LIBFT_P) clean
# 	@$(RM) $(OBJS)

# fclean: clean
# 	make -C $(LIBFT_P) fclean
# 	@$(RM) $(NAME)

# re: fclean all

# .PHONY: all clean fclean re



NAME = minishell

SOURCES = \
		srcs/main.c srcs/parsing/main1.c srcs/parsing/ft_split.c srcs/parsing/extra.c srcs/parsing/error.c \
		srcs/parsing/extra2.c srcs/parsing/file_type.c srcs/parsing/files_num_in_each_part.c \
		srcs/parsing/load_files_names.c srcs/parsing/num_of_chars_in_each_file.c srcs/parsing/qut.c \
		srcs/parsing/remove_qut_from_cmds.c srcs/parsing/trim_all.c \
		srcs/execution/builtins/echo_built_in.c srcs/execution/builtins/pwd_built_in.c srcs/execution/builtins/exit_built_in.c \
		srcs/execution/builtins/env_built_in.c srcs/execution/builtins/dict_utils.c srcs/execution/builtins/export_built_in.c \
		srcs/execution/builtins/unset_built_in.c srcs/execution/builtins/cd_built_in.c srcs/execution/builtins/sort_dictionary.c \
		srcs/execution/builtins/execute_built_ins.c srcs/execution/builtins/args_error_msgs.c srcs/execution/handle_out_file.c \
		srcs/execution/handle_in_file.c srcs/execution/check_func_path_acess.c srcs/execution/create_children.c \
		
OBJECTS = $(SOURCES:%.c=%.o)

LIBFTBF = ./includes/libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3


all: $(NAME)

$(NAME): $(OBJECTS)
	$(MAKE) -C ./includes/libft
	echo ${OBJECTS}
	$(CC) $(CFLAGS) $(SOURCES) $(LIBFTBF) -o $(NAME) -lreadline -L .brew/opt/readline/lib -I .brew/opt/readline/include
	

%.o: %.c
	${CC} ${CFLAGS} -c $< -I/usr/local/opt/readline/include -o $@

clean:
	$(MAKE) clean -C ./includes/libft
	/bin/rm -f $(OBJECTS)

fclean: clean
	$(MAKE) fclean -C ./includes/libft
	/bin/rm -f $(NAME)

re: fclean all

test: all
	@echo "\033[0;32mRunning in Valgrind.\033[0m"
	@valgrind \
	--leak-check=full \
	--track-fds=yes \
	--track-origins=yes \
	--trace-children=yes \
	--show-leak-kinds=all \
	--suppressions=supress_new \
	-s \
	./minishell

valgrind: re
	@clear
	@echo "\033[0;32mRunning in Valgrind.\033[0m"
	@valgrind \
	--leak-check=full \
	--track-fds=yes \
	--track-origins=yes \
	--show-leak-kinds=all \
	--suppressions=supress_new \
	--trace-children=yes \
	./minishell\

.PHONY: all clean fclean re valgrind
## $(CC) $(CFLAGS) $(SOURCES) $(LIBFTBF) -lreadline -o $(NAME)
## $(CC) $(CFLAGS) $(SOURCES) $(LIBFTBF) -o $(NAME) -lreadline -L .brew/opt/readline/lib -I .brew/opt/readline/include
## $(CC) $(CFLAGS) $(SOURCES) $(LIBFTBF) -lreadline -L libs -lft -L /System/Volumes/Data/usr/local/Cellar/readline/8.1/lib/libreadline.a
# $(CC) $(CFLAGS) -lreadline -L/usr/local/opt/readline/lib $(OBJECTS) ${LIBFTBF} -o $(NAME) 