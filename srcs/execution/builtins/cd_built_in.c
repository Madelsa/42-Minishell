/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:52:48 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/18 18:01:18 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// void	update_pwds(char *directory_prev, char *directory_current,
// 		t_dict **dictionary)
// {
// 	t_dict	*current;

// 	current = *dictionary;
// 	while (current != NULL)
// 	{
// 		if (ft_strcmp(current->key, "PWD") == 0)
// 		{
// 			free(current->value);
// 			current->value = ft_strdup(directory_current);
// 		}
// 		if (ft_strcmp(current->key, "OLDPWD") == 0)
// 		{
// 			free(current->value);
// 			current->value = ft_strdup(directory_prev);
// 		}
// 		current = current->next;
// 	}
// 	free(directory_current);
// 	free(directory_prev);
// }

// char	*set_directory(t_execution *exec)
// {
// 	char	*directory;

// 	directory = NULL;
// 	directory = getcwd(directory, 0);
// 	if (directory == NULL)
// 	{
// 		exec->exit_code = 1;
// 		return (ft_putstr_fd("error: cannot retrieve current directory\n", 2)
// 			, NULL);
// 	}
// 	return (directory);
// }

// char	*set_directory_home(t_dict **dictionary, t_execution *exec)
// {
// 	char	*home_path;

// 	home_path = ft_strdup("$HOME");
// 	home_path = dollar(home_path, *dictionary, exec);
	
// 	return (home_path);
// }

// int	check_file_exist(char *str, t_dict **dictionary, t_execution *exec)
// {
// 	char	*directory_prev;
// 	char	*directory_current;
// 	char	*str2;

// 	directory_current = NULL;
// 	directory_prev = set_directory(exec);
// 	// if (directory_prev == NULL)
// 	// 	return (exec->exit_code = 1);
// 	if (str == NULL || ft_strcmp(str, "~") == 0)
// 	{
// 		str2 = set_directory_home(dictionary, exec);
// 		if (chdir(str2) != -1)
// 		{
// 			directory_current = set_directory(exec);
// 			// if (directory_current == NULL)
// 			// 	return (free(directory_prev), error_msg_cd(str2, exec));
// 		}
// 		update_pwds(directory_prev, directory_current, dictionary);
// 		free(str2);
// 	}
// 	else
// 	{
// 		if (chdir(str) != -1)
// 		{
// 			directory_current = set_directory(exec);
// 			// if (directory_current == NULL)
// 			// 	return (free(directory_prev), error_msg_cd(str, exec));
// 		}
// 		directory_current = set_directory(exec);
// 		update_pwds(directory_prev, directory_current, dictionary);
// 	}
// 	return (0);
// }

// int	cd_built_in(char **arr, t_dict **dictionary, t_execution *exec)
// {
// 	if (check_file_exist(arr[1], dictionary, exec) != 0)
// 		return (exec->exit_code);
// 	exec->exit_code = 0;
// 	return (0);
// }

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
		return (ft_putstr_fd("error: cannot retrieve current directory\n", 2)
			, NULL);
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
	// if (directory_prev == NULL)
	// 	return (exec->exit_code = 1);
	flag = 0;
	if (str == NULL || ft_strcmp(str, "~") == 0)
	{
		// free(str);
		str = set_directory_home(dictionary, exec);
		flag = 1;
	}
	if (chdir(str) != -1)
		directory_current = set_directory(exec);
	if (flag == 1)
		free(str);
		// return (free(directory_prev), error_msg_cd(str, exec));
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