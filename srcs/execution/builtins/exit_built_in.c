/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:37:04 by mahmoud           #+#    #+#             */
/*   Updated: 2024/01/11 16:35:24 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../../includes/minishell.h"

void	check_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
		{
			if (i == 0)
				write(1, "exit\n", 5);
			error_msg_exit(str);
		}
		i++;
	}
}

int		exit_built_in(char **arr, int i)
{
	if (arr[1] != NULL)
		check_numeric(arr[1]);
	if (arr[1] != NULL && arr[2] != NULL)
	{
		if (i == 0)
			write(1, "exit\n", 5);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_exit_code = 1;
		exit(g_exit_code);
	}
	else
	{
		if (i == 0)
			write(1, "exit\n", 5);
		g_exit_code = 0;
		exit(g_exit_code);
	}
	return (0);
}
