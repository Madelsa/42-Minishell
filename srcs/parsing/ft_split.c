/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:45:25 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/01/05 15:12:09 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_substr_block2(char *s, unsigned int i, 
	unsigned int start, size_t len)
{
	char	*p;

	if (i - start <= len)
		p = malloc(i - start + 1);
	else
		p = malloc(len + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s[start + i] != '\0' && i < (unsigned int)len)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_substrr(char *s, unsigned int start, size_t len)
{
	char			*p;
	unsigned int	i;

	p = NULL;
	if (s == NULL)
		return (NULL);
	i = (unsigned int)ft_strlen(s);
	if (start >= i)
	{
		p = malloc(1);
		if (p == NULL)
			return (NULL);
		p[0] = '\0';
		return (p);
	}
	return (ft_substr_block2(s, i, start, len));
}

int	num_of_strs(char *s, char c)
{
	int	i;
	int	num;
	int	qut_num[2];

	i = 0;
	num = 0;
	qut_num[0] = 0;
	qut_num[1] = 0;
	// printf("xxxxxxs[0] = %d\n", s[i]);
	while (s[i] != '\0')
	{
		while (inside_qut(s, i, qut_num, 1) == 0 && s[i] == c)
			i++;
		if (s[i] == '\'' || s[i] == '"')
			inside_qut(s, i, qut_num, 1);
		if (s[i] == '\0')
			break ;
		if (s[i] != c && s[i] != '\0')
		{
			while (inside_qut(s, i, qut_num, 1) == 1 || (inside_qut(s, 
						i, qut_num, 2) == 0 && s[i] != c && s[i] != '\0'))
				i++;
		}
		// printf("xxxxxxxxxxxxxxxxxxxi: %d\n", num);
		num++;
	}
	// printf("final: %d\n", num);
	return (num);
}

char	**save_results(char *s, char c, int num, char **res)
{
	t_split	z;
	int		qut_num[2];

	z.i = 0;
	num = 0;
	qut_num[0] = 0;
	qut_num[1] = 0;
	while (s[z.i] != '\0')
	{
		while (inside_qut(s, z.i, qut_num, 1) == 0 && s[z.i] == c)
			z.i++;
		if (s[z.i] == '\'' || s[z.i] == '"')
			inside_qut(s, z.i, qut_num, 1);
		if (s[z.i] == '\0')
			break ;
		if (s[z.i] != c && s[z.i] != '\0')
		{
			z.start = z.i;
			while (inside_qut(s, z.i, qut_num, 1) == 1 || (inside_qut(s, 
						z.i, qut_num, 2) == 0 && s[z.i] != c && s[z.i] != '\0'))
			{
				// printf("> s[%d] = %c, %d\n", z.i, s[z.i], inside_qut(s, z.i, qut_num, 2));
				z.i++;
				// if (z.i == 50)
				// 	exit(1);
			}
			z.end = z.i;
		}
		res[num] = ft_substrr(s, z.start, (size_t)(z.end - z.start));
		// printf("res[%d]=%s,\n", num, res[num]);
		// printf("1 res = %s.\n", res[num]);
		if (res[num] == NULL)
			return (NULL);
		num++;
	}
	res[num] = NULL;
	return (res);
}

char	**ft_splitt(char *s, char c, t_execution *z, int is_cmds_num)
{
	int				num;
	char			**res;

	if (s == NULL)
		exit(1);
	num = num_of_strs(s, c);
	if (is_cmds_num == 1)
		z->cmds_num = num;
	// printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>num: %d\n", num);
	res = (char **)malloc(sizeof(char *) * (num + 1));
	if (res == NULL)
		exit(1);
	// printf("44444.%c,%s.\n", c, s);
	save_results(s, c, num, res);
	// printf("44444.%s,\n", res[0]);
	if (res == NULL)
		exit(1);
	return (res);
}
