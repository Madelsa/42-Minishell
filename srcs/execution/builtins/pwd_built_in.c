/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:09:09 by mahmoud           #+#    #+#             */
/*   Updated: 2024/01/11 16:35:15 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../../includes/minishell.h"

void	print_directory(void)
{
	char	*directory;

	directory = NULL;
	directory = getcwd(directory, 0);
	if (directory == NULL)
	{
		ft_putstr_fd("error: cannot retrieve current directory\n", 2);
		g_exit_code = 1;
		exit(g_exit_code);
	}
	write(1, directory, ft_strlen(directory));
	write(1, "\n", 1);
	free(directory);
}

int		pwd_built_in(char **arr)
{
	// g_exit_code = 9999;
	if (arr[1] != NULL)
	{
		if (arr[1][0] == '-')
		{
			ft_putstr_fd("error: invalid option\n", 2);
			ft_putstr_fd("pwd: usage: pwd [-LP]\n", 2);
			g_exit_code = 9999;
			exit(g_exit_code);
		}
		else
			print_directory();
	}
	else
		print_directory();
	return (0);
}
