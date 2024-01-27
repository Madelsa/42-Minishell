/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:13:32 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/28 00:37:19 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_pipes(t_execution *exec)
{
	int	i;

	i = 0;
	while (i < exec->cmds_num - 1)
	{
		if (pipe(exec->fd_pipe[i]) == -1)
		{
			write(2, "Error in pipes\n", 15);
			free_all(exec);
			ft_dict_lstclear(&exec->dictionary, free);
			// rl_clear_history();
			exit(1);
		}
		i++;
	}
}

void	close_all_fds(t_execution *exec)
{
	int	j;

	j = -1;
	while (exec->cmds_name[++j] != NULL)
	{
		if (exec->fd_infile[j] != -1)
			close(exec->fd_infile[j]);
		if (exec->fd_outfile[j] != -1)
			close(exec->fd_outfile[j]);
	}
	j = -1;
	while (exec->cmds_name[++j + 1] != NULL)
	{
		close(exec->fd_pipe[j][0]);
		close(exec->fd_pipe[j][1]);
	}
}

void	infile_error_print(t_execution *exec, int i)
{
	while (i < exec->cmds_num)
	{
		if (exec->in_file_error[i] == 1)
			ft_putstr_fd("error: No such file or directory\n", 2);
		i++;
	}
}
