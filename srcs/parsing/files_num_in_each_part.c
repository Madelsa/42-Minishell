/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_num_in_each_part.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:31:16 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/01/23 16:10:24 by aalkaisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	num_of_files_in_each_part2(char **str, t_vars *v)
{
	skip_qut(str[v->j], &v->i);
	if ((str[v->j][v->i] == '<' || str[v->j][v->i] == '>') 
		&& str[v->j][v->i] != '\'' && str[v->j][v->i] != '"')
	{
		v->symbol = know_symbol(str[v->j][v->i]);
		v->i++;
		if (str[v->j][v->i] == '<' || str[v->j][v->i] == '>')
		{
			v->symbol++;
			v->i++;
		}
		if (str[v->j][v->i] == ' ')
			v->i++;
		if (v->symbol == 1 || v->symbol == 2)
			v->size[0]++;
		else
			v->size[1]++;
	}
	if (str[v->j][v->i] == '\0')
		return (1);
	if (str[v->j][v->i] != '<' && str[v->j][v->i] != '>' 
		&& str[v->j][v->i] != '\'' && str[v->j][v->i] != '"')
		v->i++;
	return (0);
}

void	num_of_files_in_each_part(char **str, t_execution *z)
{
	t_vars	v;

	v.j = 0;
	while (str[v.j] != NULL)
	{
		v.i = 0;
		v.size[0] = 0;
		v.size[1] = 0;
		while (str[v.j][v.i] != '\0')
		{
			if (num_of_files_in_each_part2(str, &v) == 1)
				break ;
		}
		z->infile_name[v.j] = malloc(sizeof(char *) * (v.size[0] + 1));
		z->outfile_name[v.j] = malloc(sizeof(char *) * (v.size[1] + 1));
		if (z->infile_name[v.j] == NULL || z->outfile_name[v.j] == NULL)
			exit(0);
		v.j++;
	}
	z->infile_name[v.j] = NULL;
	z->outfile_name[v.j] = NULL;
}
