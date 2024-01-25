/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:35:13 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/01/25 18:47:34 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	int		i[3];
	char	*res;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (s1 == NULL || s2 == NULL || s3 == NULL)
		return (NULL);
	i[0] = ft_strlen(s1);
	i[1] = ft_strlen(s2);
	i[2] = ft_strlen(s3);
	res = malloc(i[0] + i[1] + i[2] + 1);
	if (res == NULL)
		return (NULL);
	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	while (s1[++i[0]] != '\0')
		res[i[0]] = s1[i[0]];
	while (s2[++i[1]] != '\0')
		res[i[0] + i[1]] = s2[i[1]];
	while (s3[++i[2]] != '\0')
		res[i[0] + i[1] + i[2]] = s3[i[2]];
	res[i[0] + i[1] + i[2]] = '\0';
	return (res);
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	unlink_func(t_execution *exec)
{
	int		i;
	char	*heredoc_file;

	i = -1;
	while (exec->cmds_name[++i] != NULL)
	{
		heredoc_file = heredoc_file_name("/tmp/here_doc_", i, ".tmp");
		if (access(heredoc_file, F_OK) == 0)
		{
			unlink(heredoc_file);
		}
		free(heredoc_file);
	}
}
