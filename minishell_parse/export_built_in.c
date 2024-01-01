/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:32:58 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/01 11:48:57 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_overwrite_entry(char *key, char *value, t_dict **dictionary)
{
	t_dict	*current;

	current = *dictionary;
	while (current != NULL)
	{
		if (ft_strncmp(current->key, key, ft_strlen(current->key)) == 0)
		{
			if (current->value != NULL)
				free(current->value);
			current->key = NULL;
			current->value = NULL;
			if (key)
				current->key = ft_strdup(key);
			if (value)
				current->value = ft_strdup(value);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	print_dict_export(t_dict **dictionary)
{
	t_dict	*current;

	current = *dictionary;
	while (current != NULL)
	{
		printf("declare -x  ");
		printf("%s", current->key);
		if (current->value)
			printf("=\"%s\"\n", current->value);
		else
			printf("\n");
		current = current->next;
	}
}

void	append_dict(t_dict **dictionary, char **arr, int i, int j)
{
	char	*key;
	char	*value;
	t_dict	*new_entry;

	if (arr[i][j] == '=')
	{
		key = ft_substr(arr[i], 0, j);
		value = ft_substr(arr[i], j + 1, ft_strlen(arr[i]));
		if (check_overwrite_entry(key, value, dictionary) == 0)
		{
			new_entry = ft_dict_lstnew(key, value);
			ft_dict_lstadd_back(dictionary, new_entry);
		}
		free(key);
		free(value);
	}
	else if (arr[i][j] == '\0')
	{
		if (check_overwrite_entry(arr[i], NULL, dictionary) == 0)
		{
			new_entry = ft_dict_lstnew(arr[i], NULL);
			ft_dict_lstadd_back(dictionary, new_entry);
		}
	}
}

void	handle_args(char **arr, t_dict **dictionary)
{
	int	i;
	int	j;

	i = 1;
	while (arr[i] != NULL)
	{
		j = 0;
		if (ft_isalpha(arr[i][0]) == 1)
		{
			while (arr[i][j] != '\0' && arr[i][j] != '=')
			{
				if (ft_isalnum(arr[i][j]) == 0)
				{
					printf("bash: export: not a valid identifier\n");
					break ;
				}
				j++;
			}
			append_dict(dictionary, arr, i, j);
		}
		else
			printf("bash: export: not a valid identifier\n");
		i++;
	}
}

// void sort_stack(t_dict **dictionary) {
//     int swapped = 1;

//     while (swapped) {
//         swapped = 0;
//         t_dict **current_ptr = dictionary;

//         while (*current_ptr && (*current_ptr)->next) {
//             t_dict *current = *current_ptr;
//             t_dict *next = current->next;

//             if (ft_strcmp(current->key, next->key) > 0) {
//                 current->next = next->next;
//                 next->next = current;
//                 *current_ptr = next;
//                 swapped = 1;
//             }
//             current_ptr = &((*current_ptr)->next);
//         }
//     }
// }


void sort_stack(t_dict **dictionary) {
    int swapped = 1;

    while (swapped) {
        swapped = 0;
        t_dict **current_ptr = dictionary;

        while (*current_ptr && (*current_ptr)->next) {
            t_dict *current = *current_ptr;
            t_dict *next = current->next;

            if (ft_strcmp(current->key, next->key) > 0) {
                current->next = next->next;
                next->next = current;
                *current_ptr = next;
                swapped = 1;
            }
            current_ptr = &((*current_ptr)->next);
        }
    }
}

void	export_built_in(char **arr, t_dict **dictionary)
{
	if (arr[0] != NULL)
	{
		if (ft_strncmp(arr[0], "export", 7) == 0)
		{
			if (arr[1] == NULL)
			{
				sort_stack(dictionary);
				print_dict_export(dictionary);
			}
			else
				handle_args(arr, dictionary);
		}
	}
}