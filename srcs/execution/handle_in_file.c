/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_in_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:14:04 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/25 13:22:07 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_regular_file(t_execution *exec, t_create_heredoc *data)
{
	open_input(exec->infile_name[data->i][data->j], &data->file_in, data->i,
		exec->in_file_error);
	if (exec->infile_name[data->i][data->j + 1] != NULL)
		close(data->file_in);
	else
		exec->fd_infile[data->i] = data->file_in;
}

int	process_here_doc(t_execution *exec, t_dict *dictionary,
		t_create_heredoc *data)
{
	data->heredoc_file = heredoc_file_name("/tmp/here_doc_", data->i, ".tmp");
	data->file_in = open(data->heredoc_file, O_CREAT | O_TRUNC | O_WRONLY,
			0644);
	if (data->file_in == -1)
	{
		free(data->heredoc_file);
		data->j++;
		return (1);
	}
	free(data->heredoc_file);
	exec->fd_infile[data->i] = data->file_in;
	if (here_doc(exec->infile_name[data->i][data->j], data->file_in, dictionary,
		exec) == 1)
	{
		close(data->file_in);
		exec->fd_infile[data->i] = -2;
		return (1);
	}
	close(data->file_in);
	exec->fd_infile[data->i] = -2;
	return (0);
}

void	handle_in_file(t_execution *exec, t_dict *dictionary)
{
	t_create_heredoc	data;

	data.i = 0;
	data.k = 0;
	while (exec->infile_name[data.i] != NULL)
	{
		data.j = 0;
		while (exec->infile_name[data.i][data.j] != NULL)
		{
			if (exec->is_file_or_here_doc[data.k++] == 0)
				process_regular_file(exec, &data);
			else if (exec->infile_name[data.i][data.j + 1] != NULL)
			{
				if (here_doc(exec->infile_name[data.i][data.j], -1, dictionary,
					exec) == 1)
					return ;
			}
			else if (process_here_doc(exec, dictionary, &data) == 1)
				return ;
			data.j++;
		}
		data.i++;
	}
}
