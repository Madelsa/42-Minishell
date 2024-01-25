/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:38:18 by mohammoh          #+#    #+#             */
/*   Updated: 2024/01/25 12:39:01 by aalkaisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <signal.h>
#include "libft/libft.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


extern int g_signal;



typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}	t_env;


typedef struct s_execution
{
	char	***cmds_name;       	/* cmd[0] = **args // cmd[0][0] = *cmd */ 
	char	***infile_name; 	 	/*  infile[0] = **variables before the pipe | infile[1] = after 	
									infile [0][0] = first variable for the infile */
	int		*is_file_or_here_doc;     /* zero infile | heredoc 1*/
	char	***outfile_name;    	 /* outfile[0] = **variable before the pipe .... */
	int		*is_file_or_append;  	/* is_file zero ... */
	int		*fd_infile;
	int		*fd_outfile;
	char	**full_path;
	int		**fd_pipe; 				/* 0 read | 1 write */
	// int		*infile_num; 				/* number of infile in each pipe */
	// int		*outfile_num; 			 	/* number of outfile in each pipe */
	// int		*cmds_num_in_part;
	int		cmds_num;
	int		*process_id;
	int		*in_file_error;
	int		pid;
	t_env	*env;
	int		std_in;
	int 	exit_code;
	int 	fd_std[2];
	char	**paths;
	//how many pipes?
		//loop until null (cmd[i])
		//path to it is connected with cmd[i][0] and the envp
}	t_execution;

//parsing structs
typedef struct dollar_var
{
	char				*var;
	char				*value;
	struct dollar_var	*next;
}	t_dollar_var;

typedef struct split
{
	int				i;
	unsigned int	start;
	unsigned int	end;
	int				qut_num[2];
}	t_split;

typedef struct s_vars {
	int		i;
	int		j;
	int		k;
	int		flag;
	int		symbol;
	int		num_of_chars;
	char	qut_symbol;
	int		size[2];
	int		qut_num[2];
}	t_vars;

typedef struct s_dollar {
	int		i;
	int		i2;
	int		j;
	int		qut_num[2];
	char	*dollar_word;
	int		del_dollar_flag;
	int		is_value;
}	t_dollar;

typedef struct s_replace {
	char	*str1;
	char	*str2;
	char	*value;
	char	*value2;
	int		i;
}	t_replace;

typedef struct s_dict
{
	char				*key;
	char				*value;
	struct s_dict		*next;
}						t_dict;


//builtins
int			ft_echo(char **args);
int			ft_env(t_env *env);
int			ft_export(char **args, t_env *env);
int			ft_cd(char **args, t_env *env);
int			ft_pwd(void);
int			ft_unset(char **args, t_env *env);
int			is_builtin(char *command);


//env utils
int			env_init(t_execution *mini, char **env_array);
int			env_add(char *value, t_env *env);
char		*get_env_name(char *dest, const char *src);
int			str_env_len(char **env);
void		sort_env(char **tab, int env_len);
int			is_in_env(t_env *env, char *args);
int			is_valid_env(const char *env);
int			is_in_env_remove(t_env *env, char *args);
void		print_env(t_env *env);
size_t		size_env(t_env *lst);
char		*env_to_str(t_env *lst);


//utils
int			nb_args(char **args);
int			print_error(int error, const char *arg);


//execution
int			exec_bin(char **cmd, t_env *env, t_execution *exec);
int			exec_pipe(t_execution *exec, int cmd_index);
void		exec_cmd(t_execution *exec);
int			exec_builtin(char **cmd, t_execution *exec);
void		redir(t_execution *exec, int cmd_index);
void		input(t_execution *exec, int cmd_index);
void		redir_and_exec(t_execution *exec);
char 		*heredoc_file_name(char *str, int i, char *extenstion);


//parsing
int		num_of_strs(char *s, char c);
char	**ft_splitt(char *s, char c, t_execution *z, int is_cmds_num);
void	save_results_init(int *i, int *num, int qut_num[]);
int		inside_qut(char *str, int i, int qut_num[], int time);
char	*ft_strtrimm(char *s1, char *set);
void	redirections(char *str, t_execution *z);
void	identify_file_type(char	*str, t_execution *z);
void	size_of_all_redirections(char *str, t_execution *z);
int		know_symbol(char c);
int		double_symbol_error(char *str);
int		double_pipe_error(char *str);
int		inside_qut(char *str, int i, int qut_num[], int time);
int		check_qut_error(char *str);
void	skip_qut(char *str, int *i);
int		size_after_trim(char *str);
void	ft_strtrim2(char *res, char *str, int size);
char	*ft_strtrim_all(char *str);
int		find_syntax_error(char	*str, t_execution *exec);
void	many_malloc(t_execution *z);
void	num_of_files_in_each_part(char **str, t_execution *z);
void	num_of_chars_in_each_file(char **str, t_execution *z);
void	put_chars_in_each_file(char **str, t_execution *z);
void	put_commands(char **str, t_execution *z);
void	remove_qut(t_execution *z);
void	tab_to_space(char *str);
int		in_single_or_double_qut(char *str, int i, int qut_num[], int time);
void	free_all(t_execution *exec);
char	*dollar(char *str, t_dict *dictionary, t_execution *exec);
char	*subsitute_exit_code(char *str, int i, t_execution *exec);
char	*ft_replace(char *str, t_dollar *d, t_dict *dictionary, int is_double_qut);
char	*dollar3(char *str, t_dollar *d, t_dict *dictionary);
char	*dollar6(char *str, t_dollar *d, t_dict *dictionary);
void	dollar_init(t_dollar *d);
char	*find_value_from_key(char *key, t_dict *dictionary);
int		skip_spaces(char *str);
void	unlink_func(t_execution *exec);
// void	remove_qut_from_dollar(char *dollar_str);
// void	shift_dollar(int skip, char *dollar_str);

///////////////////////////////////////////////////


//builtins funcs
int						echo_built_in(char **arr,  t_execution *exec);
int						pwd_built_in(char **arr,  t_execution *exec);
void					exit_built_in(char **arr, int i,  t_execution *exec, t_dict **dictionary);
int						env_built_in(char **arr, t_dict **dictionary,  t_execution *exec);
t_dict					*ft_dict_lstnew(char *key, char *value);
void					ft_dict_lstadd_back(t_dict **lst, t_dict *newdict);
void					ft_dict_lstclear(t_dict **lst, void (*del)(void *));
void					ft_dict_lstdelone(t_dict *lst, void (*del)(void *));
void					fill_dictionary(char **envp, t_dict **dictionary);
void					print_dictionary(t_dict **dictionary);
int						export_built_in(char **arr, t_dict **dictionary,  t_execution *exec);
int						unset_built_in(char **arr, t_dict **dictionary,  t_execution *exec);
int						cd_built_in(char **arr, t_dict **dictionary,  t_execution *exec);
void					sort_dict(t_dict **dictionary);
int						search_command_builtins(char **arr, t_dict **dictionary, int i, t_execution *exec);
int						is_builtin(char *arr);
int 					error_msg_export(char *error_arg, t_execution *exec);
void 					error_msg_exit(char *error_arg, t_execution *exec, t_dict **dictionary);
int 					error_msg_cd(char *error_arg, t_execution *exec);
int 					error_msg_unset(char *error_arg, t_execution *exec);
int						error_msg_pwd(char *error_arg, t_execution *exec);
void					handle_out_file(t_execution *exec);
void					handle_in_file(t_execution *exec, t_dict *dictionary);
char					*ft_strjoin3(char *s1, char *s2, char *s3);
void					check_func_path_acess(t_execution *exec, t_dict **dictionary);
void					open_pipes(t_execution *exec, t_dict **dictionary);
int						create_children(t_execution *exec, t_dict **dictionary);
void					close_all_fds(t_execution *exec);
void					open_heredoc_files(t_execution *exec);
void					is_parent_child_sig(int sig);
void 					rl_replace_line(const char *text, int clear_undo);
void					rl_clear_history(void);
char					*search_dict(t_dict **dictionary, char *key);
int 					error_msg_cd_home(t_execution *exec);
int						error_msg_no_path(char *error_string, t_execution *exec);
void 					prompt(t_execution *exec, t_dict *dictionary);
void					dup2_func(t_execution *exec, int i);
void					infile_error_print(t_execution *exec, int i);

#endif
