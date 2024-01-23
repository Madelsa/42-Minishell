/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_in_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:14:04 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/23 18:04:43 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_infiles_heredoc_dummy(t_execution *exec, t_dict *dictionary,
		t_create_heredoc *hdoc)
{
	if (exec->is_file_or_here_doc[hdoc->k++] == 0)
	{
		open_input(exec->infile_name[hdoc->i][hdoc->j], &hdoc->file_in, hdoc->i,
			exec->in_file_error);
		if (exec->infile_name[hdoc->i][hdoc->j + 1] != NULL)
			close(hdoc->file_in);
		else
			exec->fd_infile[hdoc->i] = hdoc->file_in;
	}
	else if (exec->infile_name[hdoc->i][hdoc->j + 1] != NULL)
	{
		here_doc(exec->infile_name[hdoc->i][hdoc->j], -1, dictionary,
			exec);
	}
}

void	heredoc_interrputed(t_execution *exec, t_create_heredoc *hdoc)
{
	close(hdoc->file_in);
	exec->fd_infile[hdoc->i] = -2;
}

int	handle_in_file2(t_execution *exec, t_dict *dictionary,
		t_create_heredoc *hdoc)
{
	while (exec->infile_name[hdoc->i][hdoc->j] != NULL)
	{
		open_infiles_heredoc_dummy(exec, dictionary, hdoc);
		hdoc->heredoc_file = heredoc_file_name("/tmp/here_doc_", hdoc->i,
				".tmp");
		hdoc->file_in = open(hdoc->heredoc_file,
				O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (hdoc->file_in == -1)
		{
			free(hdoc->heredoc_file);
			hdoc->j++;
			continue ;
		}
		free(hdoc->heredoc_file);
		exec->fd_infile[hdoc->i] = hdoc->file_in;
		if (here_doc(exec->infile_name[hdoc->i][hdoc->j], hdoc->file_in,
			dictionary, exec) == 1)
			return (heredoc_interrputed(exec, hdoc), 1);
		close(hdoc->file_in);
		exec->fd_infile[hdoc->i] = -2;
		hdoc->j++;
	}
	return (0);
}

void	handle_in_file(t_execution *exec, t_dict *dictionary)
{
	t_create_heredoc	hdoc;

	hdoc.i = 0;
	hdoc.k = 0;
	while (exec->infile_name[hdoc.i] != NULL)
	{
		hdoc.j = 0;
		if (handle_in_file2(exec, dictionary, &hdoc) == 1)
			return ;
		hdoc.i++;
	}
}

// void	handle_in_file(t_execution *exec, t_dict *dictionary)
// {
// 	int	file_in;
// 	char *heredoc_file;
// 	int	i;
// 	int	j;
// 	int	k;

// 	i = 0;
// 	k = 0;
// 	while (exec->infile_name[i] != NULL)
// 	{
// 		j = 0;
// 		while (exec->infile_name[i][j] != NULL)
// 		{
// 			if (exec->is_file_or_here_doc[k++] == 0)
// 			{
// 				printf("file: %s\n", exec->infile_name[i][j]);
				
// 				open_input(exec->infile_name[i][j], &file_in, i, exec->in_file_error);
// 				if (exec->infile_name[i][j + 1] != NULL)
// 				{
// 					printf("---->%d", file_in);
// 					close(file_in);
// 				}
// 				else
// 					exec->fd_infile[i] = file_in;
// 			}
// 			else if (exec->infile_name[i][j + 1] != NULL)
// 				here_doc(exec->infile_name[i][j], -1, dictionary, exec);
// 			else
// 			{
// 				heredoc_file = heredoc_file_name("/tmp/here_doc_", i, ".tmp");
// 				file_in = open(heredoc_file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 				if (file_in == -1)
// 				{
// 					free(heredoc_file);
// 					j++;
// 					continue ;
// 				}
// 				free(heredoc_file);
// 				exec->fd_infile[i] = file_in;
// 				if (here_doc(exec->infile_name[i][j], file_in, dictionary, exec) == 1)
// 				{
// 					// ft_putstr_fd("HERE!!!!!\n", 2);
// 					close(file_in);
// 					exec->fd_infile[i] = -2;
// 					return ;
// 				}
// 				// ft_putstr_fd("HERE!!!!!\n", 2);
// 				close(file_in);
// 				exec->fd_infile[i] = -2;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }
