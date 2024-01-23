/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:29:56 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/23 13:19:41 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_parent_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 99;
		return ;
	}
	else if (sig == SIGQUIT)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

void	handle_child_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		g_signal = 130;
		return ;
	}
	else if (sig == SIGQUIT)
	{
		g_signal = 131;
		printf("Quit: 3\n");
		return ;
	}
}

void	exit_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 1);
		close(0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 130;
	}
}

void	is_parent_child_sig(int sig)
{
	if (g_signal == 0)
		handle_child_sig(sig);
	else if (g_signal == 2)
		exit_heredoc(sig);
	else
		handle_parent_sig(sig);
}
