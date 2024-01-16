/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:09:09 by mahmoud           #+#    #+#             */
/*   Updated: 2024/01/15 17:46:48 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	print_directory(void)
{
	char	*directory;

	directory = NULL;
	directory = getcwd(directory, 0);
	if (directory == NULL)
	{
		ft_putstr_fd("error: cannot retrieve current directory\n", 2);
		g_exit_code = 1;
		return (g_exit_code);
	}
	write(1, directory, ft_strlen(directory));
	write(1, "\n", 1);
	free(directory);
	return (0);
}

int	pwd_built_in(char **arr)
{
	if (arr[1] != NULL)
	{
		if (arr[1][0] == '-' && arr[1][1] != '\0')
			return (error_msg_pwd(arr[1]));
		else if (print_directory() != 0)
			return (g_exit_code);
	}
	else if (print_directory() != 0)
		return (g_exit_code);
	return (0);
}
