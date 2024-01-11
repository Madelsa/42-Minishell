/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:52:48 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/11 10:12:05 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../../includes/minishell.h"

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

	directory_prev = NULL;
	directory_current = NULL;
	directory_prev = getcwd(directory_prev, 0);
	if (directory_prev == NULL)
	{
		g_exit_code = 1;
		return (ft_putstr_fd("error: cannot retrieve current directory\n", 2), exit(g_exit_code));
	}
	if (chdir(str) == -1)
		return (error_msg_cd(str));
	directory_current = getcwd(directory_current, 0);
	if (directory_current == NULL)
	{
		g_exit_code = 1;
		return (ft_putstr_fd("error: cannot retrieve current directory\n", 2), exit(g_exit_code));
	}
	update_pwds(directory_prev, directory_current, dictionary);
}

int	cd_built_in(char **arr, t_dict **dictionary)
{
	if (arr[1] != NULL)
		check_file_exist(arr[1], dictionary);
	return (0);
}
