/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_dictionary.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 13:31:46 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/23 16:55:21 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*search_dict(t_dict **dictionary, char *key)
{
	t_dict	*current;

	current = *dictionary;
	while (current != NULL)
	{
		if (current->key != NULL && ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
