/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:53:10 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/01/25 15:15:57 by aalkaisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dollar4(t_dollar *d)
{
	if (d->del_dollar_flag == 1)
	{
		d->i = d->i - 2;
		if (d->i < 0)
			d->i = 0;
	}
	else if (d->del_dollar_flag == 2)
		d->i--;
	d->i++;
}


char	*dollar3(char *str, t_dollar *d, t_dict *dictionary)
{
	if (d->j == 0)
	{
		d->is_value = 0;
		d->i--;
		str = ft_replace(str, d, dictionary, 0);
		d->del_dollar_flag = 1;
	}
	else if (str[d->i] >= '0' && str[d->i] <= '9')
	{
		d->is_value = 0;
		d->i--;
		d->j = 1;
		str = ft_replace(str, d, dictionary, 0);
		d->del_dollar_flag = 1;
	}
	else
	{
		d->del_dollar_flag = 1;
		d->dollar_word = ft_substr(str, d->i, d->j);
		d->is_value = 1;
		d->i--;
		str = ft_replace(str, d, dictionary, 
				in_single_or_double_qut(str, d->i, d->qut_num, 2));
	}
	return (str);
}

int	dollar2(char **str, t_dollar *d, t_execution *exec)
{
	char	*string;

	d->del_dollar_flag = 2;
	d->i++;
	string = ft_strdup(*str);
	free(*str);
	if (string[d->i] == '?')
	{
		*str = subsitute_exit_code(string, d->i, exec);
		return (1);
	}
	d->j = 0;
	while ((*str[d->j + d->i] == '_' || ft_isalnum(*str[d->j + d->i]) == 1))
		d->j++;
	if (*str[d->i] == '#')
		*str[d->i] = '0';
	return (0);
}

void	dollar5(char *str, t_dollar *d)
{
	str[d->i - 1] = ' ';
	d->del_dollar_flag = 1;
}

char	*dollar(char *str, t_dict *dictionary, t_execution *exec)
{
	t_dollar	d;

	dollar_init(&d);
	while (str[d.i] != '\0')
	{
		d.del_dollar_flag = 0;
		if ((in_single_or_double_qut(str, d.i, d.qut_num, 1) == 2 
				&& str[d.i] == '$') || (in_single_or_double_qut(str, d.i, 
					d.qut_num, 2) == 0 && str[d.i] == '$'))
		{
			if (dollar2(&str, &d, exec) == 1)
				continue ;
			if ((str[d.i] == '\'' || str[d.i] == '"') 
				&& in_single_or_double_qut(str, d.i, d.qut_num, 2) == 0)
				dollar5(str, &d);
			else if (str[d.i] == ' ' || str[d.i] == '\'' 
				|| str[d.i] == '"' || str[d.i] == '\0')
				continue ;
			else
				str = dollar6(str, &d, dictionary);
		}
		dollar4(&d);
	}
	return (str);
}
