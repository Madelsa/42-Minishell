/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:50:38 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/25 13:15:17 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*heredoc_file_name(char *str, int i, char *extenstion)
{
	char	*here_doc_file;
	char	*index;

	index = ft_itoa(i);
	here_doc_file = ft_strjoin3(str, index, extenstion);
	free(index);
	return (here_doc_file);
}

void	heredoc_write(t_inside_heredoc *in_hdoc)
{
	write(in_hdoc->fd, in_hdoc->str, ft_strlen(in_hdoc->str));
	write(in_hdoc->fd, "\n", 1);
}

int	here_doc2(t_execution *exec, t_dict *dictionary, t_inside_heredoc *in_hdoc)
{
	while (in_hdoc->str != NULL && ft_strcmp(in_hdoc->str,
			in_hdoc->limiter) != 0)
	{
		in_hdoc->str = readline(">");
		if (!in_hdoc->str)
		{
			dup2(exec->fd_std[0], 0);
			close(exec->fd_std[0]);
			return (1);
		}
		in_hdoc->str = dollar(in_hdoc->str, dictionary, exec);
		if (ft_strcmp(in_hdoc->str, in_hdoc->limiter) != 0 && in_hdoc->fd != -1)
			heredoc_write(in_hdoc);
	}
	return (0);
}

int	here_doc(char *limiter, int fd, t_dict *dictionary, t_execution *exec)
{
	t_inside_heredoc	in_hdoc;

	g_signal = 2;
	in_hdoc.limiter = limiter;
	in_hdoc.fd = fd;
	exec->fd_std[0] = dup(0);
	in_hdoc.str = readline(">");
	if (!in_hdoc.str)
	{
		dup2(exec->fd_std[0], 0);
		close(exec->fd_std[0]);
		return (1);
	}
	in_hdoc.str = dollar(in_hdoc.str, dictionary, exec);
	if (in_hdoc.str != NULL && ft_strcmp(in_hdoc.str, limiter) != 0 && fd != -1)
		heredoc_write(&in_hdoc);
	if (here_doc2(exec, dictionary, &in_hdoc) == 1)
		return (1);
	close(exec->fd_std[0]);
	g_signal = 1;
	return (0);
}
