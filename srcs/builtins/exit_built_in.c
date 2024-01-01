/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:37:04 by mahmoud           #+#    #+#             */
/*   Updated: 2024/01/01 16:29:58 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
		{
			write(1, "exit\n", 5);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	exit_built_in(char **arr)
{
	if (arr[1] != NULL)
		check_numeric(arr[1]);
	if (arr[1] != NULL && arr[2] != NULL)
	{
		write(1, "exit\n", 5);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	}
	else
	{
		write(1, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
}
