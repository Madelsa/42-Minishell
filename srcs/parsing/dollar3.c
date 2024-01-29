/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:31:19 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/01/29 11:47:41 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_replace2(t_replace *v, int is_double_qut)
{
	v->i = 0;
	while (v->value[v->i] != '\0')
	{
		if ((v->value[v->i] == '<' || v->value[v->i] == '>' 
				|| v->value[v->i] == '|') && is_double_qut == 0)
		{
			v->value2 = ft_strjoin3("\"", v->value, "\"");
			free(v->value);
			v->value = NULL;
			break ;
		}
		v->i++;
	}
	return (v->value2);
}

char	*ft_replace(char *str, t_dollar *d, 
	int is_double_qut, t_dict *dictionary)
{
	t_replace	v;

	v.value2 = NULL;
	v.value = NULL;
	v.str1 = ft_substr(str, 0, d->i);
	v.str2 = ft_substr(str, d->i + d->j + 1, ft_strlen(str) - d->i - d->j - 1);
	free(str);
	if (d->is_value == 0)
		str = ft_strjoin(v.str1, v.str2);
	else
	{
		v.value = find_value_from_key(d->dollar_word, dictionary);
		v.value2 = ft_replace2(&v, is_double_qut);
		if (v.value == NULL)
			str = ft_strjoin3(v.str1, v.value2, v.str2);
		else
			str = ft_strjoin3(v.str1, v.value, v.str2);
		if (v.value != NULL)
			free(v.value);
		if (v.value2 != NULL)
			free(v.value2);
		free(d->dollar_word);
	}
	return (free(v.str1), free(v.str2), str);
}
