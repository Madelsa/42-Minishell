/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:37:04 by mahmoud           #+#    #+#             */
/*   Updated: 2024/01/28 17:34:43 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static long	process_digits_atoi(const char *str, int sign, int i)
{
	long	result;
	long	prev;

	result = 0;
	prev = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		prev = result;
		result = result * 10 + str[i++] - '0';
		if (prev > result)
		{
			if (sign < 0)
				return (0);
			else
				return (-1);
		}
	}
	return (result * sign);
}

long	ft_atoi_ps(const char *str)
{
	int	sign;
	int	i;

	if (str == NULL)
		return (0);
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	return (process_digits_atoi(str, sign, i));
}

void	check_numeric(char *str, t_execution *exec, int j)
{
	int	i;

	i = 0;
	if ((ft_strcmp(str, "0") != 0 && ft_atoi_ps(str) == 0)
		|| (ft_strcmp(str, "-1") != 0
			&& ft_atoi_ps(str) == -1))
	{
		if (i == 0 || i == -1)
			write(1, "exit\n", 5);
		error_msg_exit(str, exec, j);
	}
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != '+' && str[i] != '-')
		{
			if (i == 0 || i == -1)
				write(1, "exit\n", 5);
			error_msg_exit(str, exec, j);
		}
		i++;
	}
}

void	exit_built_in_2(char *str, int i, t_execution *exec)
{
	if (i == 0 || i == -1)
		write(1, "exit\n", 5);
	exec->exit_code = ft_atoi_ps(str);
	free_all(exec);
	if (i == -1)
	{
		close(exec->fd_std[0]);
		close(exec->fd_std[1]);
	}
	ft_dict_lstclear(&exec->dictionary, free);
	rl_clear_history();
	exit(exec->exit_code % 256);
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
		exit_built_in_2(arr[1], i, exec);
}
