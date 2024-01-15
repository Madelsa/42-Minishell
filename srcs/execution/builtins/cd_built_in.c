/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:52:48 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/15 17:39:43 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
	free(directory_current);
	free(directory_prev);
}

char	*set_directory(void)
{
	char	*directory;

	directory = NULL;
	directory = getcwd(directory, 0);
	if (directory == NULL)
	{
		g_exit_code = 1;
		return (ft_putstr_fd("error: cannot retrieve current directory\n", 2)
			, NULL);
	}
	return (directory);
}

char	*set_directory_home(t_dict **dictionary)
{
	char	*home_path;

	home_path = ft_strdup("$HOME");
	home_path = dollar(home_path, *dictionary);
	return (home_path);
}

int	check_file_exist(char *str, t_dict **dictionary)
{
	char	*directory_prev;
	char	*directory_current;

	directory_prev = set_directory();
	if (directory_prev == NULL)
		return (g_exit_code = 1);
	if (str == NULL || ft_strcmp(str, "~") == 0)
	{
		free(str);
		str = set_directory_home(dictionary);
	}
	if (chdir(str) == -1)
		return (free(directory_prev), error_msg_cd(str));
	directory_current = set_directory();
	update_pwds(directory_prev, directory_current, dictionary);
	return (0);
}

int	cd_built_in(char **arr, t_dict **dictionary)
{
	if (check_file_exist(arr[1], dictionary) != 0)
		return (g_exit_code);
	return (0);
}
