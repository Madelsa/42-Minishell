/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_ins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:32:26 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/15 17:20:13 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	search_command_builtins(char **arr, t_dict **dictionary, int i)
{
	if (arr[0] != NULL)
	{
		if (ft_strcmp(arr[0], "exit") == 0)
			return (exit_built_in(arr, i));
		else if (ft_strcmp(arr[0], "cd") == 0)
			return (cd_built_in(arr, dictionary));
		else if (ft_strcmp(arr[0], "echo") == 0)
			return (echo_built_in(arr));
		else if (ft_strcmp(arr[0], "export") == 0)
			return (export_built_in(arr, dictionary));
		else if (ft_strcmp(arr[0], "pwd") == 0)
			return (g_exit_code = pwd_built_in(arr));
		else if (ft_strcmp(arr[0], "unset") == 0)
			return (unset_built_in(arr, dictionary));
		else if (ft_strcmp(arr[0], "env") == 0)
			return (env_built_in(arr, dictionary));
	}
	return (1);
}
