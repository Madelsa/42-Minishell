#include "../../includes/minishell.h"

void	size_of_all_redirections(char *str, t_execution *z)
{
	int		i;
	int		symbol;
	int		size[2];

	i = 0;
	size[0] = 0;
	size[1] = 0;
	if (str == NULL)
		return ;
	while (str[i] != '\0')
	{
		skip_qut(str, &i);
		if ((str[i] == '<' || str[i] == '>') && str[i] != '\'' && str[i] != '"')
		{
			symbol = know_symbol(str[i]);
			i++;
			if (str[i] == '<' || str[i] == '>')
			{
				symbol++;
				i++;
			}
			if (str[i] == ' ')
				i++;
			if (symbol == 1 || symbol == 2)
				size[0]++;
			else
				size[1]++;
		}
		if (str[i] != '<' && str[i] != '>' && str[i] != '\'' && str[i] != '"' && str[i] != '\0')
			i++;
	}
	z->is_file_or_here_doc = malloc(sizeof(int) * (size[0] + 1));
	z->is_file_or_append = malloc(sizeof(int) * (size[1] + 1));
	// z->fd_infile = malloc(sizeof(int) * size[0]);
	// z->fd_outfile = malloc(sizeof(int) * size[1]);
	if (z->is_file_or_here_doc == NULL || z->is_file_or_append == NULL)
		exit(1);
}

void	identify_file_type(char	*str, t_execution *z)
{
	int		i;
	int		symbol;
	int		size[2];

	i = 0;
	size[0] = 0;
	size[1] = 0;
	if (!str)
		return ;
	// printf("->>>>>>sttr:::%s\n", str);
	while (str[i] != '\0')
	{
		skip_qut(str, &i);
		if ((str[i] == '<' || str[i] == '>') && str[i] != '\'' && str[i] != '"')
		{
			symbol = know_symbol(str[i]);
			i++;
			if (str[i] == '<' || str[i] == '>')
			{
				symbol++;
				i++;
			}
			if (str[i] == ' ')
				i++;
			if (symbol == 1)
				z->is_file_or_here_doc[size[0]] = 0;
			else if (symbol == 2)
				z->is_file_or_here_doc[size[0]] = 1;
			else if (symbol == 3)
				z->is_file_or_append[size[1]] = 0;
			else if (symbol == 4)
				z->is_file_or_append[size[1]] = 1;
			if (symbol == 1 || symbol == 2)
				size[0]++;
			else
				size[1]++;
		}
		if (str[i] != '<' && str[i] != '>' && str[i] != '\'' && str[i] != '"' && str[i] != '\0')
			i++;
	}
	z->is_file_or_here_doc[size[0]] = -1;
	z->is_file_or_append[size[1]] = -1;
}

void	redirections(char *str, t_execution *z)
{
	// int		i;
	// int		qut_num[2];
	// // int		symbol;
	// // char	qut_symbol;
	// int		size;

	// qut_num[0] = 0;
	// qut_num[1] = 0;
	// i = 0;
	// size = 0;
	size_of_all_redirections(str, z);
	identify_file_type(str, z);
	// while (str[i] != '\0')
	// {
	// 	if (inside_qut(str, i, qut_num, 1) == 0 && 
	// 		(str[i] == '<' || str[i] == '>'))
	// 	{
	// 		symbol = know_symbol(str[i]);
	// 		i++;
	// 		if (str[i] == '<' || str[i] == '>')
	// 		{
	// 			symbol++;
	// 			i++;
	// 		}
	// 		if (str[i] == ' ')
	// 			i++;
	// 		size++;
	// 		while (inside_qut(str, i, qut_num, 1) == 1 || (inside_qut(str
	// 					, i, qut_num, 2) == 0 && str[i] != ' ' && 
	// 			str[i] != '<' && str[i] != '>'))
	// 		{
	// 			i++;
	// 		}
	// 		printf(">>>>>> %d\n", size);
	// 	}
	// 	i++;
	// }
}
