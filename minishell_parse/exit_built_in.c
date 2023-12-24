/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:37:04 by mahmoud           #+#    #+#             */
/*   Updated: 2023/12/24 16:10:52 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
		{
			write(1, "exit\n", 5);
			ft_putstr_fd("bash: exit: numeric argument required\n", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	exit_built_in(char **arr)
{
	if (arr[0] != NULL)
	{
		if (ft_strncmp(arr[0], "exit", 5) == 0)
		{
			if (arr[1] != NULL)
				check_numeric(arr[1]);
			if (arr[1] != NULL && arr[2] != NULL)
			{
				write(1, "exit\n", 5);
				ft_putstr_fd("bash: exit: too many arguments\n", 2);
			}
			else
			{
				write(1, "exit\n", 5);
				exit(EXIT_SUCCESS);
			}
		}
	}
}
