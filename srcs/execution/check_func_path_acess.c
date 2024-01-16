/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func_path_acess.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:21:12 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/05 15:37:46 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_double_pointer(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	check_func_path_acess_2(int i, int j, t_execution *exec, char	**paths)
{
	i = 0;
	while (paths[i] != NULL)
	{
		if (exec->cmds_name[j][0] != NULL && exec->cmds_name[j][0][0] != '/')
		{
			if (exec->full_path[j] != NULL)
				free(exec->full_path[j]);
			exec->full_path[j] = ft_strjoin3(paths[i], "/", 
					exec->cmds_name[j][0]);
		}
		else
			exec->full_path[j] = ft_strdup(exec->cmds_name[j][0]);
		if (exec->full_path[j] != NULL && access(exec->full_path[j], X_OK) == 0)
			break ;
		i++;
	}
	// free_complex(i, z, paths);
}

void	check_func_path_acess(char **envp, t_execution *exec)
{
	int		i;
    int     j;
	char	**paths;

	i = 0;
    // printf("TEST_5\n");
	while (envp[i] != NULL && ft_strnstr(envp[i], "PATH=",
			(size_t)5) == NULL)
		i++;
	if (envp[i] == NULL)
	{
		write(2, "PATH Error\n", 11);
        free_all(exec);
		exit(1);
	}
    // printf("TEST_4\n");
	paths = ft_split(envp[i] + 5, ':');
    // printf("TEST_1\n");
	if (paths == NULL)
		exit(1);
	j = 0;
	while (exec->cmds_name[j] != NULL)
	{
        // printf("TEST_2\n");
		exec->full_path[j] = NULL;
		check_func_path_acess_2(i, j, exec, paths);
        j++;
	}
	printf("full path: %s\n", exec->full_path[0]);
	exec->full_path[j] = NULL;
    free_double_pointer(paths);
}
