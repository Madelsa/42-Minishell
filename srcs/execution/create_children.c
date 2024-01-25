/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_children.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:58:01 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/25 18:21:15 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	single_command_and_builtin(t_execution *exec, t_dict **dictionary, int i)
{
	if (exec->cmds_name[1] == NULL)
	{
		if (is_builtin(exec->cmds_name[0][0]) == 1)
		{
			exec->fd_std[0] = dup(0);
			exec->fd_std[1] = dup(1);
			dup2_func(exec, i);
			search_command_builtins(exec->cmds_name[0], dictionary, -1, exec);
			dup2(exec->fd_std[0], 0);
			dup2(exec->fd_std[1], 1);
			close(exec->fd_std[0]);
			close(exec->fd_std[1]);
			return (1);
		}
	}
	return (0);
}

void	execute_non_builtin(t_execution *exec, t_dict **dictionary, int i)
{
	execve(exec->full_path[i], exec->cmds_name[i], exec->paths);
	rl_clear_history();
	ft_putstr_fd("Command not found\n", 2);
	free_all(exec);
	ft_dict_lstclear(dictionary, free);
	exit(127);
}

void	handle_child_process(t_execution *exec, t_dict **dictionary, int i)
{
	if (exec->process_id[i] == 0)
	{
		if (exec->in_file_error[i] == 1)
			return (free_all(exec), ft_dict_lstclear(dictionary, free),
				rl_clear_history(), exit(1));
		dup2_func(exec, i);
		close_all_fds(exec);
		if (exec->full_path[i] == NULL)
			return (free_all(exec), ft_dict_lstclear(dictionary, free),
				rl_clear_history(), exit(0));
		if (search_command_builtins(exec->cmds_name[i], dictionary, i,
				exec) != 1)
			return (free_all(exec), ft_dict_lstclear(dictionary, free),
				rl_clear_history(), exit(exec->exit_code));
		else
			execute_non_builtin(exec, dictionary, i);
	}
}

int	create_children(t_execution *exec, t_dict **dictionary)
{
	int	i;

	i = 0;
	if (single_command_and_builtin(exec, dictionary, i) == 1)
		return (1);
	infile_error_print(exec, i);
	i = 0;
	while (exec->cmds_name[i] != NULL)
	{
		g_signal = 3;
		exec->process_id[i] = fork();
		if (exec->process_id[i] < 0)
		{
			free_all(exec);
			ft_dict_lstclear(dictionary, free);
			rl_clear_history();
			exit(1);
		}
		handle_child_process(exec, dictionary, i);
		i++;
	}
	g_signal = 1;
	return (0);
}
