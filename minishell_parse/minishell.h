/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:58:00 by aalkaisi          #+#    #+#             */
/*   Updated: 2023/12/26 16:54:22 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>

typedef struct execution
{
	char	***cmds_name;
	char	***infile_name;
	int		*is_file_or_here_doc;
	char	***outfile_name;
	int		*is_file_or_append;
	int		*fd_infile;
	int		*fd_outfile;
	int		*fd_pipe[2];
	int		*infile_num;
	int		*outfile_num;
	int		*cmds_num_in_part;
	int		cmds_num;
}	t_execution;

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
}	t_split;

typedef struct s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;
}					t_dict;

int		num_of_strs(char *s, char c);
char	**ft_splitt(char *s, char c, t_execution *z);
size_t	ft_strlenn(const char *s);
int		inside_qut(char *str, int i, int qut_num[], int time);
char	*ft_strtrimm(char *s1, char *set);
int		str_cmp(char *str, char *str2);
void 	echo_built_in(char **arr);
void	pwd_built_in(char **arr);
void	exit_built_in(char **arr);
void	env_built_in(char **arr, t_dict **dictionary);
t_dict	*ft_dict_lstnew(char *key, char *value);
void	ft_dict_lstadd_back(t_dict **lst, t_dict *newdict);
void	ft_dict_lstclear(t_dict **lst, void (*del)(void *));
void	ft_dict_lstdelone(t_dict *lst, void (*del)(void *));
void	fill_dictionary(char **envp, t_dict **dictionary);
void	print_dictionary(t_dict **dictionary);
void	export_built_in(char **arr, t_dict **dictionary);
int	ft_strcmp(const char *s1, const char *s2);

#endif