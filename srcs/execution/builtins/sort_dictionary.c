/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_dictionary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:47:44 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/28 00:35:27 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../../includes/minishell.h"

void	sort_dict(t_execution *exec)
{
	int		swapped;
	t_dict	**current_head;
	t_dict	*current;
	t_dict	*next;

	swapped = 1;
	while (swapped > 0)
	{
		swapped = 0;
		current_head = &exec->dictionary;
		while (*current_head != NULL && (*current_head)->next != NULL)
		{
			current = *current_head;
			next = current->next;
			if (ft_strcmp(current->key, next->key) > 0)
			{
				current->next = next->next;
				next->next = current;
				*current_head = next;
				swapped = 1;
			}
			current_head = &((*current_head)->next);
		}
	}
}
