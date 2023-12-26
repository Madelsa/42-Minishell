/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:28:12 by mahmoud           #+#    #+#             */
/*   Updated: 2023/12/25 17:03:24 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void fill_dictionary(char **envp, t_dict **dictionary)
// {
//     char *key;
//     char *value;
//     int i = 0;
//     int j;
//     t_dict *new_entry;
   
//     while (envp[i] != NULL)
//     {
//         j = 0;
//         while (envp[i][j] != '=')
//             j++;
//         key = ft_substr(envp[i], 0, j + 1);
//         value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]));
//         // ft_printf("Key:%s\n", key);
//         // ft_printf("Value:%s\n", value);
//         new_entry = ft_dict_lstnew(key, value);
//         ft_dict_lstadd_back(dictionary, new_entry);
//         free(key);
//         free(value);
//         i++;
//     }
// }

void fill_dictionary(char **envp, t_dict **dictionary) {
    char *key;
    char *value;
    int i = 0;
    int j;
    t_dict *new_entry;
   
    while (envp[i] != NULL) {
        j = 0;
        while (envp[i][j] != '=')
            j++;
        key = ft_substr(envp[i], 0, j + 1);
        value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]));
        
        printf("Extracted Key: %s\n", key);
        printf("Extracted Value: %s\n\n", value);
        
        new_entry = ft_dict_lstnew(key, value);
        printf("New Entry Key: %s\n", new_entry->key);
        printf("New Entry Value: %s\n\n", new_entry->value);
        
        ft_dict_lstadd_back(dictionary, new_entry);
        free(key);
        free(value);
        i++;
    }
}


void	env_built_in(char **arr, char **envp, t_dict **dictionary)
{
    t_dict *current;
	if (arr[0] != NULL)
	{
		if (ft_strncmp(arr[0], "env", 4) == 0)
		{
            if (arr[1] != NULL)
            {
                ft_putstr_fd("env: No such file or directory\n", 2);
                return ;
            }
            fill_dictionary(envp, dictionary);
            current = *dictionary;
            while (current != NULL)
            {
                ft_printf("%s%s\n", current->key, current->value);
                current = current->next;
            }
            // ft_printf("test:\n", dictionary->key);
        }
    }
}