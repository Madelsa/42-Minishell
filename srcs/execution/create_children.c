/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_children.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:58:01 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/05 19:17:57 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_all_fds(t_execution *exec, int a)
{
	int	j;
	(void)a;
	// if (a == 0)
	// {
	// 	close(exec->fd_files[0]);
	// 	close(exec->fd_files[1]);
	// }
	// else
	// {
	j = -1;
	while (exec->full_path[++j] != NULL)
	{
		if (exec->fd_infile[j] != -1)
			close(exec->fd_infile[j]);
		if (exec->fd_outfile[j] != -1)
			close(exec->fd_outfile[j]);
	}
	j = -1;
	while (exec->full_path[++j + 1] != NULL)
	{
		close(exec->fd_pipe[j][0]);
		close(exec->fd_pipe[j][1]);
	}
	// }
}

void	dup2_func(t_execution *exec, int i)
{
	if (i == 0)
	{
		if (exec->fd_infile[i] != -1)
			dup2(exec->fd_infile[i], 0);
		if (exec->fd_outfile[i] != -1)
			dup2(exec->fd_outfile[i], 1);
		else if (exec->full_path[i + 1] != NULL)
			dup2(exec->fd_pipe[i][1], 1);
	}
	else if (exec->full_path[i + 1] == NULL)
	{
		if (exec->fd_infile[i] != -1)
			dup2(exec->fd_infile[i], 0);
		else
			dup2(exec->fd_pipe[i - 1][0], 0);
		if (exec->fd_outfile[i] != -1)
			dup2(exec->fd_outfile[i], 1);
	}
	else
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
}

void create_children(char **envp, t_execution *exec)
{
    int i;

    i = 0;
	while (exec->full_path[i] != NULL)
	{
		printf("infile Error: %d\n", exec->in_file_error[i]);
		i++;
	}
	i = 0;
   	while (exec->full_path[i] != NULL)
	{
		// printf("full path: %s\n", exec->full_path[i]);
		exec->process_id[i] = fork();
		if (exec->process_id[i] < 0)
			exit(1);
		if (exec->process_id[i] == 0)
		{
			// write(2, "infile Error: ", 20);
			// write(2, ft_itoa(exec->in_file_error[i]), 60);
			// write(2, "\n", 1);
			if (exec->in_file_error[i] == 1)
			{
				ft_putstr_fd("error: No such file or directory\n", 2);
				//freeall
				exit(1);
			}
			// printf("2full path: %s\n", exec->full_path[i]);
			dup2_func(exec, i);
			// printf("3full path: %s\n", exec->full_path[i]);
			close_all_fds(exec, 1);
			// printf("3full path: %s\n", exec->full_path[i]);
			execve(exec->full_path[i], exec->cmds_name[i], envp);
			write(2, "Error\n", 6);
			// while (exec->full_path[exec->i[0]] != NULL)
			// {
			// 	free(exec->full_path[exec->i[0]]);
			// 	free_list_split(exec->cmds[exec->i[0]]);
			// 	if (str_cmp("here_doc", argv[1], 0))
			// 		unlink("here_doc");
			// 	exec->i[0]++;
			// }
			exit(1);
		}
		i++;
	} 
}

void open_pipes(t_execution *exec)
{
    int	i;

	i = 0;
	while (i < exec->cmds_num - 1)
	{
		if (pipe(exec->fd_pipe[i]) == -1)
		{
			write(2, "Error in pipes\n", 15);
			// free_list(z->full_path);
			// free_cmds(z->cmds);
			// close_all_fds(z, 0, i);
			// if (str_cmp("here_doc", argv[1], 0))
			// 	unlink("here_doc");
			exit(1);
		}
		i++;
	}
}


