/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_ins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:32:26 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/02 13:24:28 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../../includes/minishell.h"

void	search_command_builtins(char **arr, t_dict **dictionary)
{
	if (arr[0] != NULL)
	{
		if (ft_strcmp(arr[0], "exit") == 0)
			exit_built_in(arr);
		else if (ft_strcmp(arr[0], "cd") == 0)
			cd_built_in(arr, dictionary);
		else if (ft_strcmp(arr[0], "echo") == 0)
			echo_built_in(arr);
		else if (ft_strcmp(arr[0], "export") == 0)
			export_built_in(arr, dictionary);
		else if (ft_strcmp(arr[0], "pwd") == 0)
			pwd_built_in(arr);
		else if (ft_strcmp(arr[0], "unset") == 0)
			unset_built_in(arr, dictionary);
		else if (ft_strcmp(arr[0], "env") == 0)
			env_built_in(arr, dictionary);
	}
}