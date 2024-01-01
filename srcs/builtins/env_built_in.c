/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:28:12 by mahmoud           #+#    #+#             */
/*   Updated: 2024/01/01 15:50:22 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_dictionary(char **envp, t_dict **dictionary)
{
	char	*key;
	char	*value;
	int		i;
	int		j;
	t_dict	*new_entry;

	i = 0;
	while (envp[i] != NULL)
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		key = ft_substr(envp[i], 0, j);
		value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]));
		new_entry = ft_dict_lstnew(key, value);
		ft_dict_lstadd_back(dictionary, new_entry);
		free(key);
		free(value);
		i++;
	}
}

void	print_dictionary(t_dict **dictionary)
{
	t_dict	*current;

	current = *dictionary;
	while (current != NULL)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void	env_built_in(char **arr, t_dict **dictionary)
{
	// if (arr[0] != NULL)
	// {
	// 	if (ft_strncmp(arr[0], "env", 4) == 0)
	// 	{
			if (arr[1] != NULL)
			{
				ft_putstr_fd("env: No such file or directory\n", 2);
				return ;
			}
			print_dictionary(dictionary);
	// 	}
	// }
}
