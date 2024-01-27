/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:37:04 by mahmoud           #+#    #+#             */
/*   Updated: 2024/01/28 00:40:02 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	check_numeric(char *str, t_execution *exec, int j)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
		{
			if (i == 0 || i == -1)
				write(1, "exit\n", 5);
			error_msg_exit(str, exec, j);
		}
		i++;
	}
}

void	exit_built_in_2(int i, t_execution *exec)
{
	if (i == 0 || i == -1)
		write(1, "exit\n", 5);
	exec->exit_code = 0;
	free_all(exec);
	if (i == -1)
	{
		close(exec->fd_std[0]);
		close(exec->fd_std[1]);
	}
	ft_dict_lstclear(&exec->dictionary, free);
	// rl_clear_history();
	exit(exec->exit_code);
}

void	exit_built_in(char **arr, int i, t_execution *exec)
{
	if (arr[1] != NULL)
		check_numeric(arr[1], exec, i);
	if (arr[1] != NULL && arr[2] != NULL)
	{
		if (i == 0 || i == -1)
			write(1, "exit\n", 5);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exec->exit_code = 1;
	}
	else
		exit_built_in_2(i, exec);
}
