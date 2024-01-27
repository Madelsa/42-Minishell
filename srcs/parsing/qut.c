/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:32:46 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/01/23 18:53:18 by aalkaisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	inside_qut(char *str, int i, int qut_num[], int time)
{
	if (time == 1)
	{
		if (str[i] == '\'' && qut_num[0] == 1)
			qut_num[0] = 0;
		else if (str[i] == '\'' && qut_num[1] == 0)
			qut_num[0] = 1;
		if (str[i] == '"' && qut_num[1] == 1)
			qut_num[1] = 0;
		else if (str[i] == '"' && qut_num[0] == 0)
			qut_num[1] = 1;
	}
	return (qut_num[0] | qut_num[1]);
}

int	in_single_or_double_qut(char *str, int i, int qut_num[], int time)
{
	if (time == 1)
	{
		if (str[i] == '\'' && qut_num[0] == 1)
			qut_num[0] = 0;
		else if (str[i] == '\'' && qut_num[1] == 0)
			qut_num[0] = 1;
		if (str[i] == '"' && qut_num[1] == 1)
			qut_num[1] = 0;
		else if (str[i] == '"' && qut_num[0] == 0)
			qut_num[1] = 1;
	}
	return (qut_num[0] + qut_num[1] * 2);
}

int	check_qut_error2(char *str, int *i)
{
	if (str[*i] == '"')
	{
		(*i)++;
		while (str[*i] != '"' && str[*i] != '\0')
			(*i)++;
		if (str[*i] == '\0')
		{
			write(2, "Qut Error\n", 10);
			return (free(str), 1);
		}
	}
	(*i)++;
	return (0);
}

int	check_qut_error(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\0')
				i++;
			if (str[i] == '\0')
			{
				write(2, "Qut Error\n", 10);
				return (free(str), 1);
			}
		}
		if (check_qut_error2(str, &i) == 1)
			return (1);
	}
	return (0);
}

void	skip_qut(char *str, int *i)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'')
			(*i)++;
		(*i)++;
	}
	if (str[*i] == '"')
	{
		(*i)++;
		while (str[*i] != '"')
			(*i)++;
		(*i)++;
	}
}
