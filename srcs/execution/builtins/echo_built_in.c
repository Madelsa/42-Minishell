/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:30:47 by mahmoud           #+#    #+#             */
/*   Updated: 2024/01/15 17:32:42 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../../includes/minishell.h"

void	write_with_line(char **arr, int i)
{
	while (arr[i] != NULL)
	{
		write(1, arr[i], ft_strlen(arr[i]));
		if (arr[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

void	write_without_line(char **arr, int i)
{
	while (arr[i] != NULL)
	{
		write(1, arr[i], ft_strlen(arr[i]));
		if (arr[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

int	check_repeat_n(char *str, int i)
{
	if (str[i] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	echo_built_in(char **arr)
{
	if (arr[1] == NULL)
		write(1, "\n", 1);
	// else if (arr[1] != NULL && ft_strcmp(arr[1], "?") == 0)
	// {
	// 	ft_putnbr_fd(g_exit_code, 2);
	// 	ft_putstr_fd("\n", 2);
	// }
	else if (arr[1] != NULL && ft_strcmp(arr[1], "-n") != 0)
	{
		if (ft_strlen(arr[1]) > 1 && check_repeat_n(arr[1], 2) == 0)
		{
			write_without_line(arr, 1);
			return (0);
		}
		write_with_line(arr, 1);
	}
	else if (arr[1] != NULL && ft_strcmp(arr[1], "-n") == 0)
		write_without_line(arr, 2);
	return (0);
}
