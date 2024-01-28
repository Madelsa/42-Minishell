/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:57:20 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/01/28 17:09:21 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_value_from_key(char *key, t_dict *dictionary)
{
	char	*value;

	value = NULL;
	while (dictionary != NULL)
	{
		if (ft_strcmp(dictionary->key, key) == 0)
		{
			value = ft_strdup(dictionary->value);
		}
		dictionary = dictionary->next;
	}
	if (value == NULL)
		value = ft_strdup("");
	return (value);
}

char	*subsitute_exit_code(char *str, int i, t_execution *exec)
{
	char	*str1;
	char	*str2;
	char	*str3;

	str1 = ft_substr(str, 0, i - 1);
	str2 = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	free(str);
	str3 = ft_itoa(exec->exit_code);
	str = ft_strjoin3(str1, str3, str2);
	return (free(str1), free(str2), free(str3), str);
}

char	*dollar6(char *str, t_dollar *d, t_dict *dictionary)
{
	str = dollar3(str, d, dictionary);
	d->i++;
	return (str);
}

void	dollar_init(t_dollar *d)
{
	d->i = 0;
	d->qut_num[0] = 0;
	d->qut_num[1] = 0;
}
