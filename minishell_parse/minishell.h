/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:58:00 by aalkaisi          #+#    #+#             */
/*   Updated: 2023/12/24 15:59:00 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

int		num_of_strs(char *s, char c);
char	**ft_split(char *s, char c, t_execution *z);
size_t	ft_strlen(const char *s);
int		inside_qut(char *str, int i, int qut_num[], int time);
char	*ft_strtrim(char *s1, char *set);
int		str_cmp(char *str, char *str2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
int		ft_isdigit(int x);
void 	echo_built_in(char **arr);
void	pwd_built_in(char **arr);
void	exit_built_in(char **arr);

#endif