/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_in_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:14:04 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/05 19:26:26 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *heredoc_file_name(char *str, int i, char *extenstion)
{
	char *here_doc_file;
	char *index;

	index = ft_itoa(i);
	here_doc_file = ft_strjoin3(str, index, extenstion);
	return (here_doc_file);
}

int	str_cmp(char *str, char *argv, int c)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0' && argv[i] != '\0' && str[i] == argv[i])
		i++;
	if (c == 1)
	{
		if (str[i] == '\n' && argv[i] == '\0')
			return (1);
	}
	else if (c == 0)
	{
		if (str[i] == '\0' && argv[i] == '\0')
			return (1);
	}
	return (0);
}

void	here_doc(char *limiter, int fd)
{
	char	*str;

	write(1, ">", 1);
	str = get_next_line(0);
	if (str != NULL && str_cmp(str, limiter, 1) == 0 && fd != -1)
		write(fd, str, ft_strlen(str));
	while (str_cmp(str, limiter, 1) == 0)
	{
		free(str);
		write(1, ">", 1);
		str = get_next_line(0);
		if (str_cmp(str, limiter, 1) == 0 && fd != -1)
			write(fd, str, ft_strlen(str));
	}
	free(str);
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

void	handle_in_file(t_execution *exec)
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
					close(file_in);
				else
					exec->fd_infile[i] = file_in;
			}
			else if (exec->infile_name[i][j + 1] != NULL)
				here_doc(exec->infile_name[i][j], -1);
			else
			{
				heredoc_file = heredoc_file_name("/tmp/here_doc_", i, ".tmp");
				file_in =	open(heredoc_file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
				exec->fd_infile[i] = file_in;
				here_doc(exec->infile_name[i][j], file_in);
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
	while (exec->full_path[++i] != NULL)
	{
		if (exec->fd_infile[i] == -2)
		{
			// j = 0;
			// while (exec->infile_name[i][j + 1] == NULL)
			// 	j++;
			heredoc_file = heredoc_file_name("/tmp/here_doc_", i, ".tmp");
			exec->fd_infile[i] = open(heredoc_file, O_RDONLY, 0644);
		}
	}
}
