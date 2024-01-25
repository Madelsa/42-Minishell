/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_ins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:32:26 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/25 11:17:16 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	search_command_builtins(char **arr, t_dict **dictionary, int i,
		t_execution *exec)
{
	if (arr[0] != NULL)
	{
		if (ft_strcmp(arr[0], "exit") == 0)
			exit_built_in(arr, i, exec, dictionary);
		else if (ft_strcmp(arr[0], "cd") == 0)
			return (cd_built_in(arr, dictionary, exec));
		else if (ft_strcmp(arr[0], "echo") == 0)
			return (echo_built_in(arr, exec));
		else if (ft_strcmp(arr[0], "export") == 0)
			return (export_built_in(arr, dictionary, exec));
		else if (ft_strcmp(arr[0], "pwd") == 0)
			return (pwd_built_in(arr, exec));
		else if (ft_strcmp(arr[0], "unset") == 0)
			return (unset_built_in(arr, dictionary, exec));
		else if (ft_strcmp(arr[0], "env") == 0)
			return (env_built_in(arr, dictionary, exec));
	}
	return (1);
}

int	is_builtin(char *arr)
{
	if (arr == NULL)
		return (0);
	if (ft_strcmp(arr, "exit") == 0 || ft_strcmp(arr, "cd") == 0
		|| ft_strcmp(arr, "echo") == 0 || ft_strcmp(arr, "export") == 0
		|| ft_strcmp(arr, "pwd") == 0 || ft_strcmp(arr, "unset") == 0
		|| ft_strcmp(arr, "env") == 0)
		return (1);
	return (0);
}
