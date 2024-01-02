/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:09:09 by mahmoud           #+#    #+#             */
/*   Updated: 2024/01/01 18:04:51 by mabdelsa         ###   ########.fr       */
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
		return ;
	}
	write(1, directory, ft_strlen(directory));
	write(1, "\n", 1);
	free(directory);
}

void	pwd_built_in(char **arr)
{
	if (arr[1] != NULL)
	{
		if (arr[1][0] == '-')
		{
			ft_putstr_fd("error: invalid option\n", 2);
			ft_putstr_fd("pwd: usage: pwd [-LP]\n", 2);
		}
		else
			print_directory();
	}
	else
		print_directory();
}
