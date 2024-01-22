/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_error_msgs2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:01:17 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/21 15:36:19 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int  error_msg_cd_home(t_execution *exec)
{
    ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd("HOME not set\n", 2);
	exec->exit_code = 1;
	return(exec->exit_code);
}