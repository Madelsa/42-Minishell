/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:52:48 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/25 16:31:58 by mabdelsa         ###   ########.fr       */
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

char	*set_directory(t_execution *exec)
{
	char	*directory;

	directory = NULL;
	directory = getcwd(directory, 0);
	if (directory == NULL)
	{
		exec->exit_code = 1;
		return (ft_putstr_fd("error: cannot retrieve current directory\n", 2),
			NULL);
	}
	return (directory);
}

char	*set_directory_home(t_dict **dictionary, t_execution *exec)
{
	char	*home_path;

	home_path = ft_strdup("$HOME");
	home_path = dollar(home_path, *dictionary, exec);
	return (home_path);
}

int	check_file_exist(char *str, t_dict **dictionary, t_execution *exec)
{
	char	*directory_prev;
	char	*directory_current;
	int		flag;

	directory_current = NULL;
	directory_prev = set_directory(exec);
	flag = 0;
	if (str == NULL || ft_strcmp(str, "~") == 0)
	{
		if (search_dict(dictionary, "HOME") == NULL)
			return (free(directory_current), free(directory_prev),
				error_msg_cd_home(exec));
		str = set_directory_home(dictionary, exec);
		flag = 1;
	}
	if (chdir(str) != -1)
		directory_current = set_directory(exec);
	if (flag == 1)
		free(str);
	update_pwds(directory_prev, directory_current, dictionary);
	return (0);
}

int	cd_built_in(char **arr, t_dict **dictionary, t_execution *exec)
{
	if (check_file_exist(arr[1], dictionary, exec) != 0)
		return (exec->exit_code);
	exec->exit_code = 0;
	return (0);
}
