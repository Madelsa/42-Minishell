/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_in_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:14:04 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/25 09:58:13 by aalkaisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *heredoc_file_name(char *str, int i, char *extenstion)
{
	char *here_doc_file;
	char *index;

	index = ft_itoa(i);
	here_doc_file = ft_strjoin3(str, index, extenstion);
	free(index);
	return (here_doc_file);
}

int	here_doc(char *limiter, int fd, t_dict *dictionary, t_execution *exec)
{
	char	*str;
	// char	*str2;
	g_signal = 2;
	exec->fd_std[0] = dup(0);
	
	str = readline(">");
	// str = ft_strdup(str2);
	if (!str)
	{
		// dup2(std_in, 0);
		// free_all(exec);
		// open("/dev/tty", O_RDONLY);
		dup2(exec->fd_std[0], 0);
		close(exec->fd_std[0]);
		return (1);
	}
	
	str = dollar(str, dictionary, exec);
	if (str != NULL && ft_strcmp(str, limiter) != 0 && fd != -1)
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
	
	while (str != NULL && ft_strcmp(str, limiter) != 0)
	{
		// free(str);
		str = readline(">");
		if (!str)
		{
			// free_all(exec);
			// open("/dev/tty", O_RDONLY);
			dup2(exec->fd_std[0], 0);
			close(exec->fd_std[0]);
			return (1);
		}
		str = dollar(str, dictionary, exec);
		// printf("dollar: %s\n", str);
		if (ft_strcmp(str, limiter) != 0 && fd != -1)
		{
			write(fd, str, ft_strlen(str));
			write(fd, "\n", 1);
		}
	}
	// dup2(std_in, 0);
	// free(str);
	// if (fd != -1)
	// 	close(fd);
	close(exec->fd_std[0]);
	g_signal = 1;
	return (0);
}

int	open_input(char *in_file_name, int *file_in, int i, int *in_file_error)
{
	*file_in = open(in_file_name, O_RDONLY, 0644);
	if (*file_in == -1)
	{
		in_file_error[i] = 1;
		printf("in_file_error[%d] = %d\n", i, in_file_error[i]);
	}
	return (0);
}

void	handle_in_file(t_execution *exec, t_dict *dictionary)
{
	int	file_in;
	char *heredoc_file;
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (exec->infile_name[i] != NULL)
	{
		j = 0;
		while (exec->infile_name[i][j] != NULL)
		{
			if (exec->is_file_or_here_doc[k++] == 0)
			{
				printf("file: %s\n", exec->infile_name[i][j]);
				
				open_input(exec->infile_name[i][j], &file_in, i, exec->in_file_error);
				if (exec->infile_name[i][j + 1] != NULL)
				{
					printf("---->%d", file_in);
					close(file_in);
				}
				else
					exec->fd_infile[i] = file_in;
			}
			else if (exec->infile_name[i][j + 1] != NULL)
			{
				if (here_doc(exec->infile_name[i][j], -1, dictionary, exec) == 1)
					return ;
			}
			else
			{
				heredoc_file = heredoc_file_name("/tmp/here_doc_", i, ".txt");
				file_in = open(heredoc_file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
				if (file_in == -1)
				{
					free(heredoc_file);
					j++;
					continue ;
				}
				free(heredoc_file);
				exec->fd_infile[i] = file_in;
				if (here_doc(exec->infile_name[i][j], file_in, dictionary, exec) == 1)
				{
					// ft_putstr_fd("HERE!!!!!\n", 2);
					close(file_in);
					exec->fd_infile[i] = -2;
					return ;
				}
				// ft_putstr_fd("HERE!!!!!\n", 2);
				close(file_in);
				exec->fd_infile[i] = -2;
			}
			j++;
		}
		i++;
	}
}

void	open_heredoc_files(t_execution *exec)
{
	int		i;
	// int		j;
	char	*heredoc_file;

	i = -1;
	// ft_putstr_fd("2HERE -->\n", 2);
	
	while (exec->cmds_name[++i] != NULL)
	{
		// ft_putstr_fd("2HERE -->\n", 2);
		if (exec->fd_infile[i] == -2)
		{
			// j = 0;
			// while (exec->infile_name[i][j + 1] == NULL)
			// 	j++;
			heredoc_file = heredoc_file_name("/tmp/here_doc_", i, ".txt");
			// ft_putstr_fd("HERE -->\n", 2);
			exec->fd_infile[i] = open(heredoc_file, O_RDONLY, 0644);
			free(heredoc_file);
		}
	}
}
