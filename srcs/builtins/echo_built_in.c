/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:30:47 by mahmoud           #+#    #+#             */
/*   Updated: 2024/01/01 15:56:32 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	echo_built_in(char **arr)
{
	if (arr[1] == NULL)
		write(1, "\n", 1);
	else if (arr[1] != NULL && ft_strncmp(arr[1], "-n", 3) != 0)
	{
		if (ft_strlen(arr[1]) > 1 && check_repeat_n(arr[1], 2) == 0)
		{
			write_without_line(arr, 1);
			return ;
		}
		write_with_line(arr, 1);
	}
	else if (arr[1] != NULL && ft_strncmp(arr[1], "-n", 3) == 0)
		write_without_line(arr, 2);
}
