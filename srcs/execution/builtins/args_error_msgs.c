/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_error_msgs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 16:49:43 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/11 09:38:31 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	error_msg_export(char *error_arg)
{
	ft_putstr_fd("minishell: export: \'", 2);
	ft_putstr_fd(error_arg, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	g_exit_code = 1;
	exit(g_exit_code);
}

void	error_msg_exit(char *error_arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(error_arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_exit_code = 255;
	exit(g_exit_code);
}

void	error_msg_cd(char *error_arg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(error_arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_exit_code = 1;
	exit(g_exit_code);
}

void	error_msg_unset(char *error_arg)
{
	ft_putstr_fd("minishell: unset: \'", 2);
	ft_putstr_fd(error_arg, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	g_exit_code = 1;
	exit(g_exit_code);
}
