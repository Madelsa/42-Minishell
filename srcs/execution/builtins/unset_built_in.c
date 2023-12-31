/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:48:28 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/01 18:04:57 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../../includes/minishell.h"


void	check_errors(char **arr)
{
	int	i;
	int	j;

	i = 1;
	while (arr[i] != NULL)
	{
		j = 0;
		if (!ft_isalpha(arr[i][0]))
		{
			error_msg_unset(arr[i]);
			i++;
			continue ;
		}
		while (arr[i][j] != '\0')
		{
			if (!ft_isalnum(arr[i][j]))
			{
				error_msg_unset(arr[i]);
				break ;
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
	if (arr[1] != NULL)
	{
		check_errors(arr);
		check_in_dictionary(arr, dictionary);
	}
}
