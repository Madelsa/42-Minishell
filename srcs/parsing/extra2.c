/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:30:59 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/01/29 11:25:31 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tab_to_space(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != '\0')
	{
		skip_qut(str, &i);
		if (str[i] == '\t')
			str[i] = ' ';
		if (str[i] != '\'' && str[i] != '"' && str[i] != '\0')
			i++;
	}
}

int	know_symbol(char c)
{
	int	symbol;

	if (c == '<')
		symbol = 1;
	else
		symbol = 3;
	return (symbol);
}

void	many_malloc2(t_execution *z)
{
	z->cmds_name = malloc(sizeof(char **) * (z->cmds_num + 1));
	z->infile_name = malloc(sizeof(char **) * (z->cmds_num + 1));
	z->outfile_name = malloc(sizeof(char **) * (z->cmds_num + 1));
	z->fd_infile = malloc(sizeof(int) * z->cmds_num);
	z->fd_outfile = malloc(sizeof(int) * z->cmds_num);
	z->full_path = ft_calloc((z->cmds_num + 1), sizeof(char *));
	z->fd_pipe = malloc(sizeof(int *) * z->cmds_num);
	z->process_id = malloc(sizeof(int) * z->cmds_num);
	z->in_out_file_error = malloc(sizeof(int) * z->cmds_num);
	if (z->cmds_name == NULL || z->infile_name == NULL 
		|| z->outfile_name == NULL || z->fd_infile == NULL 
		|| z->fd_outfile == NULL || z->full_path == NULL 
		|| z->fd_pipe == NULL || z->process_id == NULL 
		|| z->in_out_file_error == NULL)
		exit(1);
}

void	many_malloc(t_execution *z)
{
	int	i;

	many_malloc2(z);
	i = 0;
	while (i < z->cmds_num)
	{
		z->fd_infile[i] = -1;
		z->fd_outfile[i] = -1;
		i++;
	}
	i = -1;
	while (++i < z->cmds_num - 1)
		z->fd_pipe[i] = malloc(sizeof(int) * 2);
	z->fd_pipe[i] = NULL;
	i = -1;
	while (++i < z->cmds_num)
		z->in_out_file_error[i] = 0;
}

void	put_commands(char **str, t_execution *z)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		z->cmds_name[i] = ft_splitt(str[i], ' ', z, 0);
		i++;
	}
	z->cmds_name[i] = NULL;
}
