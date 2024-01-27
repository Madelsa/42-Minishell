/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:33:07 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/01/23 17:51:52 by aalkaisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	size_after_trim(char *str)
{
	int		i;
	int		size;
	char	flag;
	int		qut_num[2];

	i = 0;
	size = 0;
	flag = 'N';
	qut_num[0] = 0;
	qut_num[1] = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] != '\0' && flag == 'Y')
			size++;
		while (inside_qut(str, i, qut_num, 1) == 1 || 
			(str[i] != ' ' && str[i] != '\0'))
		{
			size++;
			i++;
			flag = 'Y';
		}
	}
	return (size);
}

void	ft_strtrim2_init(t_vars *v)
{
	v->i = 0;
	v->flag = 'N';
	v->qut_num[0] = 0;
	v->qut_num[1] = 0;
}

void	ft_strtrim2(char *res, char *str, int size)
{
	t_vars	v;

	ft_strtrim2_init(&v);
	while (str[v.i] != '\0')
	{
		while (str[v.i] == ' ')
			v.i++;
		if (str[v.i] != '\0' && v.flag == 'Y')
		{
			res[size] = ' ';
			size++;
		}
		while (inside_qut(str, v.i, v.qut_num, 1) == 1 || 
			(str[v.i] != ' ' && str[v.i] != '\0'))
		{
			res[size] = str[v.i];
			size++;
			v.i++;
			v.flag = 'Y';
		}
	}
	free(str);
	res[size] = '\0';
}

char	*ft_strtrim_all(char *str)
{
	int		size;
	char	*res;

	if (str == NULL)
		return (NULL);
	size = size_after_trim(str);
	res = (char *)malloc(size + 1);
	if (res == NULL)
		return (NULL);
	size = 0;
	ft_strtrim2(res, str, size);
	return (res);
}
