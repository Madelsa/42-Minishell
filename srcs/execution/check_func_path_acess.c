/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func_path_acess.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:21:12 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/22 12:45:21 by aalkaisi         ###   ########.fr       */
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
		if (exec->full_path[j] != NULL)
				free(exec->full_path[j]);
		if (exec->cmds_name[j][0] != NULL && exec->cmds_name[j][0][0] != '/' && exec->cmds_name[j][0][0] != '.')
		{
			exec->full_path[j] = ft_strjoin3(paths[i], "/", 
					exec->cmds_name[j][0]);
		}
		else
		{
			exec->full_path[j] = ft_strdup(exec->cmds_name[j][0]);
			break ;
		}
		if (exec->full_path[j] != NULL && access(exec->full_path[j], X_OK) == 0)
			break ;
		i++;
	}
	// free_complex(i, z, paths);
}

void	check_func_path_acess(t_execution *exec,  t_dict **dictionary)
{
	int		i;
    int     j;
	char	*path;
	i = 0;
	path = search_dict(dictionary, "PATH");
	if (path == NULL)
	{
		while (*exec->cmds_name[i] != NULL && is_builtin(*exec->cmds_name[i]) == 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(*exec->cmds_name[i], 2);
			ft_putstr_fd(" No such file or directory\n", 2);
			exec->exit_code = 127;
		i++;
		if (i == exec->cmds_num)
			prompt(exec, *dictionary);
			
		}
	}
	
	// while (envp[i] != NULL && ft_strnstr(envp[i], "PATH=",
	// 		(size_t)5) == NULL)
	// 	i++;
	
	// if (envp[i] == NULL)
	// {
	// 	write(2, "PATH Error\n", 11);
    //     // free_all(exec);
	// 	exit(1);
	// 	// rl_redisplay();
	// }
    // printf("TEST_4\n");
	i = 0;
	if (path != NULL)
		exec->paths = ft_split(path + 5, ':');
    // printf("TEST_1\n");
	// if (exec->paths == NULL)
	// 	exit(1);
	j = 0;
	while (exec->cmds_name[j] != NULL)
	{
        // printf("TEST_2\n");
		exec->full_path[j] = NULL;
		check_func_path_acess_2(i, j, exec, exec->paths);
        j++;
	}
	i = 0;
	// while (exec->paths[i])
	// {
	// 	printf("paths: %s\n", exec->paths[i]);
	// }
	// printf("full path: %s\n", exec->full_path[0]);
	exec->full_path[j] = NULL;
    // free_double_pointer(exec->paths);
}
