/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:26:50 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/03 15:58:45 by mabdelsa         ###   ########.fr       */
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

void	handle_out_file(t_execution *exec)
{
	int	file_out;
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (exec->outfile_name[i] != NULL)
	{
		j = 0;
		while (exec->outfile_name[i][j] != NULL)
		{
			if (exec->is_file_or_append[k] == 0)
				file_out = open_trunc(exec->outfile_name[i][j]);
			else
				file_out = open_append(exec->outfile_name[i][j]);
			if (exec->outfile_name[i][j + 1] != NULL)
				close(file_out);
			j++;
			k++;
		}
		i++;
	}
}
