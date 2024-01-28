/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:09:09 by mahmoud           #+#    #+#             */
/*   Updated: 2024/01/28 17:09:21 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	print_directory(t_execution *exec)
{
	char	*directory;

	directory = NULL;
	directory = getcwd(directory, 0);
	if (directory == NULL)
	{
		ft_putstr_fd("error: cannot retrieve current directory\n", 2);
		exec->exit_code = 1;
		return (exec->exit_code);
	}
	write(1, directory, ft_strlen(directory));
	write(1, "\n", 1);
	free(directory);
	return (0);
}

int	pwd_built_in(char **arr, t_execution *exec)
{
	if (arr[1] != NULL)
	{
		if (arr[1][0] == '-' && arr[1][1] != '\0')
			return (error_msg_pwd(arr[1], exec));
		else if (print_directory(exec) != 0)
			return (exec->exit_code);
	}
	else if (print_directory(exec) != 0)
		return (exec->exit_code);
	return (0);
}
