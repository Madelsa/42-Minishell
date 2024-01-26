/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func_path_acess.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:21:12 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/26 13:05:50 by mabdelsa         ###   ########.fr       */
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

void	check_func_path_acess_2(int i, int j, t_execution *exec, char **paths)
{
	i = 0;
	while (paths[i] != NULL)
	{
		if (exec->full_path[j] != NULL)
			free(exec->full_path[j]);
		if (exec->cmds_name[j][0] != NULL && exec->cmds_name[j][0][0] != '/'
			&& exec->cmds_name[j][0][0] != '.')
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
}

void	split_paths(t_execution *exec, char *path)
{
	int	i;
	int	j;

	i = 0;
	if (path != NULL)
	{
		exec->paths = ft_split(path + 5, ':');
		j = 0;
		while (exec->cmds_name[j] != NULL)
		{
			exec->full_path[j] = NULL;
			check_func_path_acess_2(i, j, exec, exec->paths);
			j++;
		}
		exec->full_path[j] = NULL;
	}
}

void	check_func_path_acess(t_execution *exec, t_dict **dictionary)
{
	int		i;
	char	*path;

	i = 0;
	path = search_dict(dictionary, "PATH");
	if (path == NULL)
	{
		while (*exec->cmds_name[i] != NULL
			&& is_builtin(*exec->cmds_name[i]) == 0)
		{
			error_msg_no_path(*exec->cmds_name[i], exec);
			exec->exit_code = 127;
			i++;
			if (i == exec->cmds_num)
			{
				exec->paths = NULL;
				free_all(exec);
				prompt(exec, *dictionary);
			}
		}
		exec->paths = NULL;
	}
	split_paths(exec, path);
}
