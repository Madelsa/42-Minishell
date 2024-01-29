/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:38:18 by mohammoh          #+#    #+#             */
/*   Updated: 2024/01/29 11:23:43 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>

extern int				g_signal;

typedef struct s_dict
{
	char				*key;
	char				*value;
	struct s_dict		*next;
}						t_dict;

typedef struct s_execution
{
	char				***cmds_name;
	char				***infile_name;

	int					*is_file_or_here_doc;
	char				***outfile_name;
	int					*is_file_or_append;
	int					*fd_infile;
	int					*fd_outfile;
	char				**full_path;
	int					**fd_pipe;
	int					cmds_num;
	int					*process_id;
	int					*in_out_file_error;
	int					pid;
	int					std_in;
	int					exit_code;
	int					fd_std[2];
	char				**paths;
	char				**envp;
	t_dict				*dictionary;
}						t_execution;

typedef struct dollar_var
{
	char				*var;
	char				*value;
	struct dollar_var	*next;
}						t_dollar_var;

typedef struct split
{
	int					i;
	unsigned int		start;
	unsigned int		end;
	int					qut_num[2];
}						t_split;

typedef struct s_vars
{
	int					i;
	int					j;
	int					k;
	int					flag;
	int					symbol;
	int					num_of_chars;
	char				qut_symbol;
	int					size[2];
	int					qut_num[2];
}						t_vars;

typedef struct s_create_heredoc
{
	char				*heredoc_file;
	int					file_in;
	int					i;
	int					j;
	int					k;
}						t_create_heredoc;

typedef struct s_inside_heredoc
{
	char				*str;
	char				*limiter;
	int					fd;
}						t_inside_heredoc;

typedef struct s_dollar
{
	int					i;
	int					i2;
	int					j;
	int					qut_num[2];
	char				*dollar_word;
	int					del_dollar_flag;
	int					is_value;
}						t_dollar;

typedef struct s_replace
{
	char				*str1;
	char				*str2;
	char				*value;
	char				*value2;
	int					i;
}						t_replace;

int						num_of_strs(char *s, char c);
char					**ft_splitt(char *s, char c, t_execution *z,
							int is_cmds_num);
void					save_results_init(int *i, int *num, int qut_num[]);
int						inside_qut(char *str, int i, int qut_num[], int time);
char					*ft_strtrimm(char *s1, char *set);
void					redirections(char *str, t_execution *z);
void					identify_file_type(char *str, t_execution *z);
void					size_of_all_redirections(char *str, t_execution *z);
int						know_symbol(char c);
int						double_symbol_error(char *str);
int						double_pipe_error(char *str);
int						inside_qut(char *str, int i, int qut_num[], int time);
int						check_qut_error(char *str);
void					skip_qut(char *str, int *i);
int						size_after_trim(char *str);
void					ft_strtrim2(char *res, char *str, int size);
char					*ft_strtrim_all(char *str);
int						find_syntax_error(char *str, t_execution *exec);
void					many_malloc(t_execution *z);
void					num_of_files_in_each_part(char **str, t_execution *z);
void					num_of_chars_in_each_file(char **str, t_execution *z);
void					put_chars_in_each_file(char **str, t_execution *z);
void					put_commands(char **str, t_execution *z);
void					remove_qut(t_execution *z);
void					tab_to_space(char *str);
int						in_single_or_double_qut(char *str, int i, int qut_num[],
							int time);
void					free_all(t_execution *exec);
char					*dollar(char *str, t_dict *dictionary,
							t_execution *exec);
char					*subsitute_exit_code(char *str, int i,
							t_execution *exec);
char					*ft_replace(char *str, t_dollar *d, int is_double_qut,
							t_dict *dictionary);
char					*dollar3(char *str, t_dollar *d, t_dict *dictionary);
char					*dollar6(char *str, t_dollar *d, t_dict *dictionary);
void					dollar_init(t_dollar *d);
char					*find_value_from_key(char *key, t_dict *dictionary);
int						skip_spaces(char *str);
void					unlink_func(t_execution *exec);

int						echo_built_in(char **arr, t_execution *exec);
int						pwd_built_in(char **arr, t_execution *exec);
void					exit_built_in(char **arr, int i, t_execution *exec);
int						env_built_in(char **arr, t_execution *exec);
t_dict					*ft_dict_lstnew(char *key, char *value);
void					ft_dict_lstadd_back(t_dict **lst, t_dict *newdict);
void					ft_dict_lstclear(t_dict **lst, void (*del)(void *));
void					ft_dict_lstdelone(t_dict *lst, void (*del)(void *));
void					fill_dictionary(char **envp, t_execution *exec);
void					print_dictionary(t_execution *exec);
int						export_built_in(char **arr, t_execution *exec);
int						unset_built_in(char **arr, t_execution *exec);
int						cd_built_in(char **arr, t_execution *exec);
void					sort_dict(t_execution *exec);
int						search_command_builtins(char **arr, int i,
							t_execution *exec);
int						is_builtin(char *arr);
int						error_msg_export(char *error_arg, t_execution *exec);
void					error_msg_exit(char *error_arg, t_execution *exec,
							int j);
int						error_msg_cd(char *error_arg, t_execution *exec);
int						error_msg_unset(char *error_arg, t_execution *exec);
int						error_msg_pwd(char *error_arg, t_execution *exec);
void					handle_out_file(t_execution *exec);
void					handle_in_file(t_execution *exec);
char					*ft_strjoin3(char *s1, char *s2, char *s3);
void					check_func_path_acess(t_execution *exec);
void					open_pipes(t_execution *exec);
int						create_children(t_execution *exec);
void					close_all_fds(t_execution *exec);
void					open_heredoc_files(t_execution *exec);
void					is_parent_child_sig(int sig);
void					rl_replace_line(const char *text, int clear_undo);
void					rl_clear_history(void);
char					*search_dict(t_execution *exec, char *key);
int						error_msg_cd_home(t_execution *exec);
int						error_msg_no_path(char *error_string,
							t_execution *exec);
void					prompt(t_execution *exec);
void					dup2_func(t_execution *exec, int i);
void					infile_error_print(t_execution *exec, int i);
int						open_input(char *in_file_name, int *file_in, int i,
							int *in_out_file_error);
int						here_doc(char *limiter, int fd, t_execution *exec);
char					*heredoc_file_name(char *str, int i, char *extenstion);
size_t					ft_dict_lstsize(t_dict *lst);
void					create_envp(t_execution *exec);
#endif
