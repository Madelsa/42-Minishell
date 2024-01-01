// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   minishell_parse.h                                  :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/10/09 14:58:00 by aalkaisi          #+#    #+#             */
// /*   Updated: 2023/12/05 19:39:58 by mohammoh         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #ifndef MINISHELL_parse_H
// # define MINISHELL_parse_H

// # include <stdio.h>
// # include <unistd.h>
// # include <stdlib.h>
// # include <readline/readline.h>
// # include "../../includes/minishell.h"

// typedef struct s_vars {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		flag;
// 	int		symbol;
// 	int		num_of_chars;
// 	char	qut_symbol;
// 	int		size[2];
// 	int		qut_num[2];
// } t_vars;


// // typedef struct execution
// // {
// // 	char	***cmds_name;
// // 	char	***infile_name;
// // 	int		*is_file_or_here_doc;
// // 	char	***outfile_name;
// // 	int		*is_file_or_append;
// // 	int		*fd_infile;
// // 	int		*fd_outfile;
// // 	int		*fd_pipe[2];
// // 	int		*infile_num;
// // 	int		*outfile_num;
// // 	int		*cmds_num_in_part;
// // 	int		cmds_num;
// // }	t_execution;

// typedef struct dollar_var
// {
// 	char				*var;
// 	char				*value;
// 	struct dollar_var	*next;
// }	t_dollar_var;

// typedef struct split
// {
// 	int				i;
// 	unsigned int	start;
// 	unsigned int	end;
// }	t_split;

// int		num_of_strs(char *s, char c);
// char	**ft_splitt(char *s, char c, t_execution *z);
// // size_t	ft_strlen(const char *s);
// int		inside_qut(char *str, int i, int qut_num[], int time);
// // char	*ft_strtrim(char *s1, char *set);
// int		str_cmp(char *str, char *str2);
// void	redirections(char *str, t_execution *z);
// void	identify_file_type(char	*str, t_execution *z);
// void	size_of_all_redirections(char *str, t_execution *z);
// int		know_symbol(char c);
// int		double_symbol_error(char *str);
// int		double_pipe_error(char *str);
// int		inside_qut(char *str, int i, int qut_num[], int time);
// int		check_qut_error(char *str);
// int		skip_qut(char *str, int *i);
// int		size_after_trim(char *str);
// void	ft_strtrim2(char *res, char *str, int size);
// char	*ft_strtrim_all(char *str);
// int		find_syntax_error(char	*str);
// void	many_malloc(t_execution *z);
// void	num_of_files_in_each_part(char **str, t_execution *z);
// void	num_of_chars_in_each_file(char **str, t_execution *z);
// void	put_chars_in_each_file(char **str, t_execution *z);
// void	put_commands(char **str, t_execution *z);
// void	remove_qut(t_execution *z);
// void	check_solution(t_execution *z);
// void	tab_to_space(char *str);



// #endif