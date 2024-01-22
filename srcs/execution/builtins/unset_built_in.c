/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:48:28 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/17 18:15:02 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_errors(char **arr, t_execution *exec)
{
	int	i;
	int	j;

	i = 1;
	while (arr[i] != NULL)
	{
		j = 0;
		if (ft_isalpha(arr[i][0]) == 0)
		{
			error_msg_unset(arr[i], exec);
			i++;
			continue ;
		}
		while (arr[i][j] != '\0')
		{
			if (ft_isalnum(arr[i][j]) == 0)
				return (error_msg_unset(arr[i], exec));
			j++;
		}
		i++;
	}
	return (0);
}

void	remove_from_dict(char *str, t_dict **dictionary)
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
			return ;
		}
		prev = current;
		current = current->next;
	}
	return ;
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

int	unset_built_in(char **arr, t_dict **dictionary, t_execution *exec)
{
	if (arr[1] != NULL)
	{
		if (check_errors(arr, exec) != 0)
			return (exec->exit_code);
		check_in_dictionary(arr, dictionary);
	}
	return (0);
}
