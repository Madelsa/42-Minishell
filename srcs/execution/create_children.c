/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_children.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:58:01 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/22 19:20:46 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_all_fds(t_execution *exec)
{
	int	j;

	j = -1;
	while (exec->full_path[++j] != NULL)
	{
		if (exec->fd_infile[j] != -1)
		{
			printf("close in file\n");
			close(exec->fd_infile[j]);
		}
		if (exec->fd_outfile[j] != -1)
		{
			printf("close out file\n");
			close(exec->fd_outfile[j]);
		}
	}
	j = -1;
	while (exec->full_path[++j + 1] != NULL)
	{
		printf("close pipe\n");
		close(exec->fd_pipe[j][0]);
		close(exec->fd_pipe[j][1]);
	}
}

// void	dup2_func(t_execution *exec, int i)
// {
// 	if (i == 0)
// 	{
// 		if (exec->fd_infile[i] != -1)
// 			dup2(exec->fd_infile[i], 0);
// 		if (exec->fd_outfile[i] != -1)
// 		{
// 			ft_putnbr_fd(exec->fd_outfile[i], 2);
// 			dup2(exec->fd_outfile[i], 1);
// 		}
// 		else if (exec->full_path[i + 1] != NULL)
// 			dup2(exec->fd_pipe[i][1], 1);
// 	}
// 	else if (exec->full_path[i + 1] == NULL)
// 	{
// 		if (exec->fd_infile[i] != -1)
// 			dup2(exec->fd_infile[i], 0);
// 		else
// 			dup2(exec->fd_pipe[i - 1][0], 0);
// 		if (exec->fd_outfile[i] != -1)
// 			dup2(exec->fd_outfile[i], 1);
// 	}
// 	else
// 	{
// 		if (exec->fd_infile[i] != -1)
// 			dup2(exec->fd_infile[i], 0);
// 		else
// 			dup2(exec->fd_pipe[i - 1][0], 0);
// 		if (exec->fd_outfile[i] != -1)
// 			dup2(exec->fd_outfile[i], 1);
// 		else
// 			dup2(exec->fd_pipe[i][1], 1);
// 	}
// }

int	create_children(t_execution *exec, t_dict **dictionary)
{
	int	i;

	i = 0;
	if (exec->cmds_name[1] == NULL)
	{
		if (is_builtin(exec->cmds_name[0][0]) == 1)
		{
			exec->fd_std[0] = dup(0);
			exec->fd_std[1] = dup(1);
			dup2_func(exec, i);
			search_command_builtins(exec->cmds_name[0], dictionary, 0, exec);
			dup2(exec->fd_std[0], 0);
			dup2(exec->fd_std[1], 1);
			close(exec->fd_std[0]);
			close(exec->fd_std[1]);
			return (1);
		}
	}
	while (i < exec->cmds_num)
	{
		if (exec->in_file_error[i] == 1)
			ft_putstr_fd("error: No such file or directory\n", 2);
		i++;
	}
	i = 0;
	while (exec->full_path[i] != NULL)
	{
		g_signal = 0;
		exec->process_id[i] = fork();
		if (exec->process_id[i] < 0)
		{
			free_all(exec);
			ft_dict_lstclear(dictionary, free);
			rl_clear_history();
			exit(1);
		}
		if (exec->process_id[i] == 0)
		{
			if (exec->in_file_error[i] == 1)
			{
				free_all(exec);
				ft_dict_lstclear(dictionary, free);
				rl_clear_history();
				exit(1);
			}
			dup2_func(exec, i);
			close_all_fds(exec);
			if (search_command_builtins(exec->cmds_name[i], dictionary, i,
					exec) != 1)
			{
				free_all(exec);
				ft_dict_lstclear(dictionary, free);
				rl_clear_history();
				exit(exec->exit_code);
			}
			else
			{
				execve(exec->full_path[i], exec->cmds_name[i], exec->paths);
				rl_clear_history();
				ft_putstr_fd("command not found\n", 2);
				free_all(exec);
				ft_dict_lstclear(dictionary, free);
				exit(1);
			}
		}
		i++;
	}
	return (0);
}

void	open_pipes(t_execution *exec, t_dict **dictionary)
{
	int	i;

	i = 0;
	while (i < exec->cmds_num - 1)
	{
		if (pipe(exec->fd_pipe[i]) == -1)
		{
			write(2, "Error in pipes\n", 15);
			free_all(exec);
			ft_dict_lstclear(dictionary, free);
			rl_clear_history();
			exit(1);
		}
		i++;
	}
}
