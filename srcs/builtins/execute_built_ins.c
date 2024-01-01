/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_ins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:32:26 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/01 15:50:52 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	search_command_builtins(char **arr, t_dict **dictionary)
{
	if (arr[0] != NULL)
	{
		if (ft_strncmp(arr[0], "exit", 5) == 0)
			exit_built_in(arr);
		else if (ft_strncmp(arr[0], "cd", 3) == 0)
			cd_built_in(arr, dictionary);
		else if (ft_strncmp(arr[0], "echo", 5) == 0)
			echo_built_in(arr);
		else if (ft_strncmp(arr[0], "export", 7) == 0)
			export_built_in(arr, dictionary);
		else if (ft_strncmp(arr[0], "pwd", 4) == 0)
			pwd_built_in(arr);
		else if (ft_strncmp(arr[0], "unset", 6) == 0)
			unset_built_in(arr, dictionary);
		else if (ft_strncmp(arr[0], "env", 4) == 0)
			env_built_in(arr, dictionary);
	}
}