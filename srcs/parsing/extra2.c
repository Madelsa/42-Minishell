#include "../../includes/minishell.h"

// char	*ft_strdup(const char *s1)
// {
// 	char	*p;
// 	int		i;

// 	i = 0;
// 	while (s1[i] != '\0')
// 		i++;
// 	p = (char *)malloc(sizeof(char) * (i + 1));
// 	if (p == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i] != '\0')
// 	{
// 		p[i] = s1[i];
// 		i++;
// 	}
// 	p[i] = '\0';
// 	return (p);
// }

void	tab_to_space(char *str)
{
	int	i;
	// int	qut_num[2];

	i = 0;
	// qut_num[0] = 0;
	// qut_num[1] = 0;
	if (str == NULL)
		return ;
	while (str[i] != '\0')
	{
		skip_qut(str, &i);
		if (str[i] == '\t')
			str[i] = ' ';
		if (str[i] != '\'' && str[i] != '"' && str[i] != '\0')
			i++;
	}
}

// void	find_qut_error(char *str)
// {
// 	int	i;
// 	int	qut_num[2];

// 	qut_num[0] = 0;
// 	qut_num[1] = 0;
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		inside_qut(str, i, qut_num);
// 		i++;
// 	}
// 	if (qut_num[0] == 1 || qut_num[1] == 1)
// 		exit(1);
// }

int	know_symbol(char c)
{
	int	symbol;

	if (c == '<')
		symbol = 1;
	else
		symbol = 3;
	return (symbol);
}

// int	know_qut_symbol(char c)
// {
// 	int	symbol;

// 	if (c == '\'')
// 		symbol = 1;
// 	else
// 		symbol = 2;
// 	return (symbol);
// }

void	many_malloc(t_execution *z)
{
	z->cmds_name = malloc(sizeof(char **) * (z->cmds_num + 1));
	z->infile_name = malloc(sizeof(char **) * (z->cmds_num + 1));
	z->outfile_name = malloc(sizeof(char **) * (z->cmds_num + 1));
	if (z->cmds_name == NULL || z->infile_name == NULL || 
		z->outfile_name == NULL)
		exit(1);
}



// void	num_of_commands_in_each_part(char **str, t_execution *z)
// {
// 	int		j;

// 	j = 0;
// 	while (str[j] != NULL)
// 	{
// 		z->cmds_name[j] = ft_split(str[j], ' ', z);
// 		// if (z->cmds_name[j][0][0] != '\0')
// 		j++;
// 	}
// 	z->cmds_name[j] = NULL;
// }

void	put_commands(char **str, t_execution *z)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		z->cmds_name[i] = ft_splitt(str[i], ' ', z);
		i++;
	}
	z->cmds_name[i] = NULL;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
