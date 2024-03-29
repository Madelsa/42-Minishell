/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:29:44 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/01/29 12:41:47 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	double_pipe_error(char *str)
{
	int	i;
	int	symbol;
	int	qut_num[2];

	i = 0;
	symbol = 0;
	qut_num[0] = 0;
	qut_num[1] = 0;
	while (str[i] != '\0')
	{
		if (inside_qut(str, i, qut_num, 1) == 0)
		{
			if (str[i] == '|' && symbol == 1)
				return (1);
			if (str[i] != ' ' && symbol == 1)
				symbol = 0;
			if (str[i] == '|' && symbol == 0)
				symbol = 1;
		}
		i++;
	}
	return (0);
}

int	double_symbol_error2(char *str, int *i, int qut_num[], int *symbol)
{
	if (inside_qut(str, *i, qut_num, 2) == 0 && str[*i] == '>' && *symbol == 0)
	{
		(*i)++;
		if (inside_qut(str, *i, qut_num, 1) == 0 && str[*i] == '>')
		{
			*symbol = 4;
			(*i)++;
		}
		else
			*symbol = 3;
	}
	else if (inside_qut(str, *i, qut_num, 2) == 0 && (str[*i] == '|' || 
			str[*i] == '<' || str[*i] == '>') && *symbol != 0)
		return (1);
	if (str[*i] != ' ' && str[*i] != '<' && str[*i] != '>' && str[*i] != '|')
		*symbol = 0;
	(*i)++;
	return (0);
}

void	double_symbol_error_init(int *i, int *symbol, int qut_num[])
{
	*i = 0;
	*symbol = 0;
	qut_num[0] = 0;
	qut_num[1] = 0;
}

int	double_symbol_error(char *str)
{
	int	i;
	int	symbol;
	int	qut_num[2];

	double_symbol_error_init(&i, &symbol, qut_num);
	while (str[i] != '\0')
	{
		if (inside_qut(str, i, qut_num, 1) == 0 && str[i] == '<' && symbol == 0)
		{
			i++;
			if (inside_qut(str, i, qut_num, 1) == 0 && str[i] == '<')
			{
				symbol = 2;
				i++;
			}
			else
				symbol = 1;
		}
		else
		{
			if (double_symbol_error2(str, &i, qut_num, &symbol) == 1)
				return (1);
		}
	}
	return (0);
}

int	find_syntax_error(char	*str, t_execution *exec)
{
	int	str_len;

	str_len = ft_strlen(str);
	if (str[0] == '|' || str[str_len - 1] == '|' || 
		str[str_len - 1] == '<' || 
		str[str_len - 1] == '>')
	{
		ft_putstr_fd("syntax error\n", 2);
		free(str);
		exec->exit_code = 258;
		return (1);
	}
	if (double_pipe_error(str) == 1 || double_symbol_error(str) == 1)
	{
		ft_putstr_fd("syntax error\n", 2);
		free(str);
		exec->exit_code = 258;
		return (1);
	}
	return (0);
}
