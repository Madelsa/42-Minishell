/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:32:58 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/28 00:42:41 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../../includes/minishell.h"

int	check_overwrite_entry(char *key, char *value, t_execution *exec)
{
	t_dict	*current;

	current = exec->dictionary;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0) 
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

void	print_dict_export(t_execution *exec)
{
	t_dict	*current;

	current = exec->dictionary;
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

void	append_dict(t_execution *exec ,char **arr, int i, int j)
{
	char	*key;
	char	*value;
	t_dict	*new_entry;

	if (arr[i][j] == '=')
	{
		key = ft_substr(arr[i], 0, j);
		value = ft_substr(arr[i], j + 1, ft_strlen(arr[i]));
		if (check_overwrite_entry(key, value, exec) == 0)
		{
			new_entry = ft_dict_lstnew(key, value);
			ft_dict_lstadd_back(&exec->dictionary, new_entry);
		}
		free(key);
		free(value);
	}
	else if (arr[i][j] == '\0')
	{
		if (check_overwrite_entry(arr[i], NULL, exec) == 0)
		{
			new_entry = ft_dict_lstnew(arr[i], NULL);
			ft_dict_lstadd_back(&exec->dictionary, new_entry);
		}
	}
}

int	handle_args(char **arr, t_execution *exec)
{
	int	i;
	int	j;

	i = 1;
	while (arr[i] != NULL)
	{
		j = 1;
		if (ft_isalpha(arr[i][0]) == 1 || arr[i][0] == '_')
		{
			while (arr[i][j] != '\0' && arr[i][j] != '=')
			{
				if (ft_isalnum(arr[i][j]) == 0)
					return (error_msg_export(arr[i], exec));
				j++;
			}
			append_dict(exec, arr, i, j);
		}
		else
			return (error_msg_export(arr[i], exec));
		i++;
	}
	return (0);
}

int	export_built_in(char **arr, t_execution *exec)
{
	if (arr[1] == NULL)
	{
		sort_dict(exec);
		print_dict_export(exec);
	}
	else
		if (handle_args(arr, exec) != 0)
			return (exec->exit_code);
	return (0);
}
