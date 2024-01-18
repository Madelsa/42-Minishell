/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:37:04 by mahmoud           #+#    #+#             */
/*   Updated: 2024/01/18 17:51:32 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../../includes/minishell.h"

void	check_numeric(char *str, t_execution *exec)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
		{
			if (i == 0)
				write(1, "exit\n", 5);
			error_msg_exit(str, exec);
		}
		i++;
	}
}

void	exit_built_in(char **arr, int i, t_execution *exec, t_dict **dictionary)
{
	if (arr[1] != NULL)
		check_numeric(arr[1], exec);
	if (arr[1] != NULL && arr[2] != NULL)
	{
		if (i == 0)
			write(1, "exit\n", 5);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exec->exit_code = 1;
		ft_dict_lstclear(dictionary, free);
		free_all(exec);
		close(exec->fd_std[0]);
		close(exec->fd_std[1]);
		exit(exec->exit_code);
	}
	else
	{
		if (i == 0)
			write(1, "exit\n", 5);
		exec->exit_code = 0;
		ft_dict_lstclear(dictionary, free);
		free_all(exec);
		close(exec->fd_std[0]);
		close(exec->fd_std[1]);
		exit(exec->exit_code);
	}
}
