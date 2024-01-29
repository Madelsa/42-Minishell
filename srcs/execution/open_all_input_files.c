/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_all_input_files.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:46:16 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/29 11:24:17 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_heredoc_files(t_execution *exec)
{
	int		i;
	char	*heredoc_file;

	i = -1;
	while (exec->cmds_name[++i] != NULL)
	{
		if (exec->fd_infile[i] == -2)
		{
			heredoc_file = heredoc_file_name("/tmp/here_doc_", i, ".tmp");
			exec->fd_infile[i] = open(heredoc_file, O_RDONLY, 0644);
			free(heredoc_file);
		}
	}
}

int	open_input(char *in_file_name, int *file_in, int i, int *in_out_file_error)
{
	*file_in = open(in_file_name, O_RDONLY, 0644);
	if (*file_in == -1)
		in_out_file_error[i] = 1;
	return (0);
}
