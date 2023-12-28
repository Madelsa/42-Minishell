/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:48:28 by mabdelsa          #+#    #+#             */
/*   Updated: 2023/12/28 14:24:40 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_errors(char **arr)
{
	int	i;
	int	j;

	i = 1;
	while (arr[i] != NULL)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			if (ft_isalpha(arr[i][0]) == 0 || ft_isalnum(arr[i][j] == 0))
			{
				ft_putstr_fd("bash: unset: not a valid identifier\n", 2);
				return ;
			}
			j++;
		}
		i++;
	}
}

int	remove_from_dict(char *str, t_dict **dictionary)
{
	t_dict	*current;
	t_dict	*prev;

	current = *dictionary;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, str) == 0)
		{
			if (prev != NULL)
				prev->next = current->next;
			else
				*dictionary = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

void	check_in_dictionary(char **arr, t_dict **dictionary)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		remove_from_dict(arr[i], dictionary);
		i++;
	}
}

void	unset_built_in(char **arr, t_dict **dictionary)
{
	if (arr[0] != NULL)
	{
		if (ft_strncmp(arr[0], "unset", 6) == 0)
		{
			if (arr[1] != NULL)
			{
				check_errors(arr);
				check_in_dictionary(arr, dictionary);
			}
		}
	}
}
