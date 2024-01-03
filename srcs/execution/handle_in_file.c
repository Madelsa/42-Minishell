/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_in_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:14:04 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/01/03 17:02:51 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	str_cmp(char *str, char *argv, int c)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0' && argv[i] != '\0' && str[i] == argv[i])
		i++;
	if (c == 1)
	{
		if (str[i] == '\n' && argv[i] == '\0')
			return (1);
	}
	else if (c == 0)
	{
		if (str[i] == '\0' && argv[i] == '\0')
			return (1);
	}
	return (0);
}

void	here_doc(char **argv, int fd)
{
	char	*str;

	str = get_next_line(0);
	if (str != NULL && str_cmp(str, argv[2], 1) == 0)
		write(fd, str, ft_strlen(str));
	while (str_cmp(str, argv[2], 1) == 0)
	{
		free(str);
		str = get_next_line(0);
		if (str_cmp(str, argv[2], 1) == 0)
			write(fd, str, ft_strlen(str));
	}
	free(str);
}

int	open_input(char *in_file_name, int *file_in)
{
	*file_in = open(in_file_name, O_RDONLY, 0644);
	if (*file_in == -1)
	{
		ft_putstr_fd("error: No such file or directory\n", 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	handle_out_file(t_execution *exec)
{
	int	file_in;
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (exec->infile_name[i] != NULL)
	{
		j = 0;
		while (exec->infile_name[i][j] != NULL)
		{
			if (exec->is_file_or_here_doc[k] == 0)
				open_input(exec->infile_name[i][j], &file_in);
			else
				here_doc();
			if (exec->infile_name[i][j + 1] != NULL)
				close(file_in);
			j++;
			k++;
		}
		i++;
	}
}
