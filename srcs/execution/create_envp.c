/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:46:12 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/28 14:33:38 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_envp(t_execution *exec)
{
	size_t	dict_count;
	t_dict	*current;
	char	*temp;
	int		i;

	i = 0;
	dict_count = ft_dict_lstsize(exec->dictionary);
	exec->envp = ft_calloc(dict_count + 1, sizeof(char *));
	current = exec->dictionary;
	while (current != NULL)
	{
		temp = ft_strjoin(current->key, "=");
		exec->envp[i] = ft_strjoin(temp, current->value);
		free(temp);
		current = current->next;
		i++;
	}
}
