/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:05:55 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/01/29 11:25:52 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all3(t_execution *exec)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (exec->outfile_name[i] != NULL)
	{
		j = 0;
		while (exec->outfile_name[i][j] != NULL)
		{
			free(exec->outfile_name[i][j]);
			j++;
		}
		free(exec->outfile_name[i]);
		i++;
	}
	free(exec->outfile_name);
	free(exec->is_file_or_here_doc);
	free(exec->is_file_or_append);
}

void	free_all2(t_execution *exec)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (exec->infile_name[i] != NULL)
	{
		j = 0;
		while (exec->infile_name[i][j] != NULL)
		{
			free(exec->infile_name[i][j]);
			j++;
		}
		free(exec->infile_name[i]);
		i++;
	}
	free(exec->infile_name);
}

void	free_all4(t_execution *exec)
{
	int	i;

	i = 0;
	if (exec->full_path != NULL)
	{
		i = 0;
		while (exec->cmds_name[i] != NULL)
		{
			if (exec->full_path[i] != NULL)
				free(exec->full_path[i]);
			i++;
		}
		free(exec->full_path);
	}
	i = 0;
	if (exec->envp != NULL)
	{
		while (exec->envp[i] != NULL)
		{
			free(exec->envp[i]);
			i++;
		}
		free(exec->envp);
	}
}

void	free_all5(t_execution *exec)
{
	int	i;

	free(exec->fd_infile);
	free(exec->fd_outfile);
	i = 0;
	while (i < exec->cmds_num - 1)
	{
		free(exec->fd_pipe[i]);
		i++;
	}
	i = 0;
	if (exec->paths != NULL)
	{
		while (exec->paths[i] != NULL)
		{
			free(exec->paths[i]);
			i++;
		}
		free(exec->paths);
	}
	free(exec->fd_pipe);
	free(exec->process_id);
	free(exec->in_out_file_error);
}

void	free_all(t_execution *exec)
{
	int	i;
	int	j;

	free_all2(exec);
	free_all3(exec);
	free_all4(exec);
	i = 0;
	j = 0;
	while (exec->cmds_name[i] != NULL)
	{
		j = 0;
		while (exec->cmds_name[i][j] != NULL)
		{
			free(exec->cmds_name[i][j]);
			j++;
		}
		free(exec->cmds_name[i]);
		i++;
	}
	free(exec->cmds_name);
	free_all5(exec);
}
