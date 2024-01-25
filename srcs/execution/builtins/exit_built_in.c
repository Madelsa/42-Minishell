/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:37:04 by mahmoud           #+#    #+#             */
/*   Updated: 2024/01/23 13:27:31 by aalkaisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../../includes/minishell.h"

void	check_numeric(char *str, t_execution *exec, t_dict **dictionary)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
		{
			if (i == 0)
				write(1, "exit\n", 5);
			error_msg_exit(str, exec, dictionary);
		}
		i++;
	}
}

void	exit_built_in(char **arr, int i, t_execution *exec, t_dict **dictionary)
{
	if (arr[1] != NULL)
		check_numeric(arr[1], exec, dictionary);
	if (arr[1] != NULL && arr[2] != NULL)
	{
		if (i == 0)
			write(1, "exit\n", 5);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exec->exit_code = 1;
		free_all(exec);
		close(exec->fd_std[0]);
		close(exec->fd_std[1]);
	}
	else
	{
		if (i == 0)
			write(1, "exit\n", 5);
		exec->exit_code = 0;
		free_all(exec);
		close(exec->fd_std[0]);
		close(exec->fd_std[1]);
	}
	ft_dict_lstclear(dictionary, free);
	// rl_clear_history();
	exit(exec->exit_code);
}
