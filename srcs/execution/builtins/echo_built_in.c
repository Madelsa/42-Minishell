/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:30:47 by mahmoud           #+#    #+#             */
/*   Updated: 2024/01/11 16:36:36 by mahmoud          ###   ########.fr       */
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
	else if (arr[1] != NULL && ft_strcmp(arr[1], "?") == 0)
	{
		ft_putnbr_fd(g_exit_code, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (arr[1] != NULL && ft_strncmp(arr[1], "-n", 3) != 0)
	{
		if (ft_strlen(arr[1]) > 1 && check_repeat_n(arr[1], 2) == 0)
		{
			write_without_line(arr, 1);
			exit(0);
		}
		write_with_line(arr, 1);
	}
	else if (arr[1] != NULL && ft_strncmp(arr[1], "-n", 3) == 0)
		write_without_line(arr, 2);
	return (0);
}
