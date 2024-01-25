/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:30:02 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/01/23 14:24:00 by aalkaisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	start_index(char *s1, char *set)
{
	int	skip;
	int	start;
	int	i;

	start = 0;
	skip = 1;
	while (s1[start] != '\0' && skip == 1)
	{
		i = 0;
		skip = 0;
		while (set[i] != '\0' && skip == 0)
		{
			if (set[i] == s1[start])
			{
				start++;
				skip = 1;
			}
			i++;
		}
	}
	return (start);
}

int	end_index(int end, char *s1, char *set)
{
	int	skip;
	int	i;

	skip = 1;
	while (end != -1 && skip == 1)
	{
		i = 0;
		skip = 0;
		while (set[i] != '\0' && skip == 0)
		{
			if (set[i] == s1[end])
			{
				end--;
				skip = 1;
			}
			i++;
		}
	}
	return (end);
}

char	*ft_strtrimm(char *s1, char *set)
{
	int		start;
	int		i;
	int		end;
	char	*res;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = start_index(s1, set);
	end = ft_strlen(s1) - 1;
	if (s1[start] == '\0')
		start = 0;
	end = end_index(end, s1, set);
	res = (char *)malloc(end - start + 2);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (start + i <= end)
	{
		res[i] = s1[start + i];
		i++;
	}
	res[i] = '\0';
	free(s1);
	return (res);
}
