/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_of_chars_in_each_file.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:32:33 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/01/23 17:07:07 by aalkaisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	num_of_chars_in_each_file2(char **str, t_vars *v)
{
	if (str[v->j][v->i] == '<' || str[v->j][v->i] == '>')
	{
		v->symbol++;
		v->i++;
	}
	if (str[v->j][v->i] == ' ')
		v->i++;
	v->num_of_chars = 0;
	while (inside_qut(str[v->j], v->i, v->qut_num, 1) == 1 
		|| (inside_qut(str[v->j], v->i, v->qut_num, 2) == 0 
			&& str[v->j][v->i] != ' ' && str[v->j][v->i] != '<' 
		&& str[v->j][v->i] != '>' && str[v->j][v->i] != '\0'))
	{
		if (inside_qut(str[v->j], v->i, v->qut_num, 2) == 1 
			&& (str[v->j][v->i] == '\'' || str[v->j][v->i] == '"') 
			&& (v->qut_symbol == str[v->j][v->i] || v->qut_symbol == 'N'))
			v->qut_symbol = str[v->j][v->i];
		else if (inside_qut(str[v->j], v->i, v->qut_num, 2) == 0 
			&& v->qut_symbol == str[v->j][v->i])
			v->qut_symbol = 'N';
		else
			v->num_of_chars++;
		v->i++;
	}
}

int	num_of_chars_in_each_file3(char **str, t_execution *z, t_vars *v)
{
	if (inside_qut(str[v->j], v->i, v->qut_num, 1) == 0 && 
		(str[v->j][v->i] == '<' || str[v->j][v->i] == '>'))
	{
		v->symbol = know_symbol(str[v->j][v->i]);
		v->i++;
		num_of_chars_in_each_file2(str, v);
		if (v->symbol == 1 || v->symbol == 2)
			z->infile_name[v->j][v->size[0]] = malloc(v->num_of_chars + 1);
		else
			z->outfile_name[v->j][v->size[1]] = malloc(v->num_of_chars + 1);
		if (v->symbol == 1 || v->symbol == 2)
			v->size[0]++;
		else
			v->size[1]++;
	}
	if (inside_qut(str[v->j], v->i, v->qut_num, 2) == 1 
		|| (str[v->j][v->i] != '<' && str[v->j][v->i] != '>' 
		&& str[v->j][v->i] != '\0'))
		v->i++;
	if (str[v->j][v->i] == '\0')
		return (1);
	return (0);
}

void	num_of_chars_in_each_file(char **str, t_execution *z)
{
	t_vars	v;

	v.j = 0;
	v.qut_num[0] = 0;
	v.qut_num[1] = 0;
	v.qut_symbol = 'N';
	while (str[v.j] != NULL)
	{
		v.i = 0;
		v.size[0] = 0;
		v.size[1] = 0;
		while (str[v.j][v.i] != '\0')
		{
			if (num_of_chars_in_each_file3(str, z, &v))
				continue ;
		}
		z->infile_name[v.j][v.size[0]] = NULL;
		z->outfile_name[v.j][v.size[1]] = NULL;
		v.j++;
	}
}
