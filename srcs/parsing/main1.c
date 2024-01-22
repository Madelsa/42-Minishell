/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:55:17 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/01/18 12:56:06 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_solution(t_execution *z)
{
	int i = 0;
	int j = 0;

	while (z->infile_name[i] != NULL)
	{
		j = 0;
		while (z->infile_name[i][j] != NULL)
		{
			// printf("z->infile_name[%d][%d]: %s,\n", i, j, z->infile_name[i][j]);
			j++;
		}
		i++;
	}
	i = 0;
	j = 0;
	while (z->outfile_name[i] != NULL)
	{
		j = 0;
		while (z->outfile_name[i][j] != NULL)
		{
			// printf("z->outfile_name[%d][%d]: %s,\n", i, j, z->outfile_name[i][j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (z->is_file_or_here_doc[i] != -1)
	{
		// printf("z->is_file_or_here_doc[%d]: %d\n", i, z->is_file_or_here_doc[i]);
		i++;
	}
	i = 0;
	while (z->is_file_or_append[i] != -1)
	{
		printf("z->is_file_or_append[%d]: %d\n", i, z->is_file_or_append[i]);
		i++;
	}
	i = 0;
	j = 0;
	while (z->cmds_name[i] != NULL)
	{
		j = 0;
		while (z->cmds_name[i][j] != NULL)
		{
			// printf("z->cmds_name[%d][%d]: %s,\n", i, j, z->cmds_name[i][j]);
			j++;
		}
		i++;
	}
}
