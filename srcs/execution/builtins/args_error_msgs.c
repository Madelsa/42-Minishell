/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_error_msgs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 16:49:43 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/21 15:02:28 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	error_msg_export(char *error_arg, t_execution *exec)
{
	ft_putstr_fd("minishell: export: \'", 2);
	ft_putstr_fd(error_arg, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	exec->exit_code = 1;
	return (exec->exit_code);
}

void	error_msg_exit(char *error_arg, t_execution *exec)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(error_arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exec->exit_code = 255;
	exit(exec->exit_code);
}

int	error_msg_cd(char *error_arg, t_execution *exec)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(error_arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exec->exit_code = 1;
	return (exec->exit_code);
}

int	error_msg_unset(char *error_arg, t_execution *exec)
{
	ft_putstr_fd("minishell: unset: \'", 2);
	ft_putstr_fd(error_arg, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	exec->exit_code = 1;
	exit(exec->exit_code);
}

int	error_msg_pwd(char *error_arg, t_execution *exec)
{
	ft_putstr_fd("minishell: pwd: ", 2);
	ft_putstr_fd(error_arg, 2);
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("pwd: usage: pwd [-LP]\n", 2);
	exec->exit_code = 1;
	return (exec->exit_code);
}
