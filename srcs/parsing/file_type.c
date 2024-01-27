/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:31:08 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/01/23 15:24:42 by aalkaisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	size_of_all_redirections2(char *str, int i, int size[])
{
	int	symbol;

	while (str[i] != '\0')
	{
		skip_qut(str, &i);
		if ((str[i] == '<' || str[i] == '>') && str[i] != '\'' && str[i] != '"')
		{
			symbol = know_symbol(str[i]);
			i++;
			if (str[i] == '<' || str[i] == '>')
			{
				symbol++;
				i++;
			}
			if (str[i] == ' ')
				i++;
			if (symbol == 1 || symbol == 2)
				size[0]++;
			else
				size[1]++;
		}
		if (str[i] != '<' && str[i] != '>' && str[i] != '\'' 
			&& str[i] != '"' && str[i] != '\0')
			i++;
	}
}

void	size_of_all_redirections(char *str, t_execution *z)
{
	int		i;
	int		size[2];

	i = 0;
	size[0] = 0;
	size[1] = 0;
	if (str == NULL)
		return ;
	size_of_all_redirections2(str, i, size);
	z->is_file_or_here_doc = malloc(sizeof(int) * (size[0] + 1));
	z->is_file_or_append = malloc(sizeof(int) * (size[1] + 1));
	if (z->is_file_or_here_doc == NULL || z->is_file_or_append == NULL)
		exit(1);
}

void	identify_file_type2(char *str, t_execution *z, t_vars *v)
{
	if ((str[v->i] == '<' || str[v->i] == '>') 
		&& str[v->i] != '\'' && str[v->i] != '"')
	{
		v->symbol = know_symbol(str[v->i]);
		v->i++;
		if (str[v->i] == '<' || str[v->i] == '>')
		{
			v->symbol++;
			v->i++;
		}
		if (str[v->i] == ' ')
			v->i++;
		if (v->symbol == 1)
			z->is_file_or_here_doc[v->size[0]] = 0;
		else if (v->symbol == 2)
			z->is_file_or_here_doc[v->size[0]] = 1;
		else if (v->symbol == 3)
			z->is_file_or_append[v->size[1]] = 0;
		else if (v->symbol == 4)
			z->is_file_or_append[v->size[1]] = 1;
		if (v->symbol == 1 || v->symbol == 2)
			v->size[0]++;
		else
			v->size[1]++;
	}
}

void	identify_file_type(char	*str, t_execution *z)
{
	t_vars	v;

	v.i = 0;
	v.size[0] = 0;
	v.size[1] = 0;
	if (!str)
		return ;
	while (str[v.i] != '\0')
	{
		skip_qut(str, &v.i);
		identify_file_type2(str, z, &v);
		if (str[v.i] != '<' && str[v.i] != '>' && str[v.i] != '\'' 
			&& str[v.i] != '"' && str[v.i] != '\0')
			v.i++;
	}
	z->is_file_or_here_doc[v.size[0]] = -1;
	z->is_file_or_append[v.size[1]] = -1;
}

void	redirections(char *str, t_execution *z)
{
	size_of_all_redirections(str, z);
	identify_file_type(str, z);
}
