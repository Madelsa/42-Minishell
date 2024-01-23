/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:53:33 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/23 14:45:03 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	first_command(t_execution *exec, int i)
{
	if (exec->fd_infile[i] != -1)
		dup2(exec->fd_infile[i], 0);
	if (exec->fd_outfile[i] != -1)
		dup2(exec->fd_outfile[i], 1);
	else if (exec->full_path[i + 1] != NULL)
		dup2(exec->fd_pipe[i][1], 1);
}

void	final_command(t_execution *exec, int i)
{
	if (exec->fd_infile[i] != -1)
		dup2(exec->fd_infile[i], 0);
	else
		dup2(exec->fd_pipe[i - 1][0], 0);
	if (exec->fd_outfile[i] != -1)
		dup2(exec->fd_outfile[i], 1);
}

void	middle_commands(t_execution *exec, int i)
{
	if (exec->fd_infile[i] != -1)
		dup2(exec->fd_infile[i], 0);
	else
		dup2(exec->fd_pipe[i - 1][0], 0);
	if (exec->fd_outfile[i] != -1)
		dup2(exec->fd_outfile[i], 1);
	else
		dup2(exec->fd_pipe[i][1], 1);
}

void	dup2_func(t_execution *exec, int i)
{
	if (i == 0)
		first_command(exec, i);
	else if (exec->full_path[i + 1] == NULL)
		final_command(exec, i);
	else
		middle_commands(exec, i);
}
