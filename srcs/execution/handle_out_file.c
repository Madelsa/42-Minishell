/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_out_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:26:50 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/28 19:27:55 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_trunc(char *out_file_name)
{
	return (open(out_file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644));
}

int	open_append(char *out_file_name)
{
	return (open(out_file_name, O_CREAT | O_APPEND | O_WRONLY, 0644));
}

int	open_out_file(t_execution *exec, int i, int j, int k)
{
	int	file_out;

	if (exec->is_file_or_append[k] == 0)
		file_out = open_trunc(exec->outfile_name[i][j]);
	else
		file_out = open_append(exec->outfile_name[i][j]);
	return (file_out);
}

void	close_or_set_fd_outfile(t_execution *exec, int i, int j, int *file_out)
{
	if (exec->outfile_name[i][j + 1] != NULL)
		close(*file_out);
	else
		exec->fd_outfile[i] = *file_out;
}

void	handle_out_file(t_execution *exec)
{
	int	i;
	int	j;
	int	k;
	int	file_out;

	i = 0;
	k = 0;
	while (exec->outfile_name[i] != NULL)
	{
		j = 0;
		while (exec->outfile_name[i][j] != NULL)
		{
			file_out = open_out_file(exec, i, j, k);
			if (file_out == -1)
			{
				j++;
				k++;
				continue ;
			}
			close_or_set_fd_outfile(exec, i, j, &file_out);
			j++;
			k++;
		}
		i++;
	}
}
