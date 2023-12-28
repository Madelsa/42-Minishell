/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:52:48 by mabdelsa          #+#    #+#             */
/*   Updated: 2023/12/28 16:43:35 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwds(char *directory_prev, char *directory_current,
		t_dict **dictionary)
{
	t_dict	*current;

	current = *dictionary;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, "PWD") == 0)
		{
			free(current->value);
			current->value = ft_strdup(directory_current);
		}
		if (ft_strcmp(current->key, "OLDPWD") == 0)
		{
			free(current->value);
			current->value = ft_strdup(directory_prev);
		}
		current = current->next;
	}
}

void	check_file_exist(char *str, t_dict **dictionary)
{
	char	*directory_prev;
	char	*directory_current;

    printf("HERE!!!!\n");
	directory_prev = NULL;
	directory_current = NULL;
	directory_prev = getcwd(directory_prev, 0);
	if (directory_prev == NULL)
	{
		ft_putstr_fd("Error: cannot retrieve current directory\n", 2);
		return ;
	}
	if (chdir(str) == -1)
	{
		ft_putstr_fd("bash: cd: No such file or directory\n", 2);
		return ;
	}
	directory_current = getcwd(directory_current, 0);
	if (directory_current == NULL)
	{
		ft_putstr_fd("Error: cannot retrieve current directory\n", 2);
		return ;
	}
	update_pwds(directory_prev, directory_current, dictionary);
}

void	cd_built_in(char **arr, t_dict **dictionary)
{
	if (arr[0] != NULL)
	{
		if (ft_strncmp(arr[0], "cd", 3) == 0)
		{
			if (arr[1] != NULL)
				check_file_exist(arr[1], dictionary);
		}
	}
}
