#include "../../includes/minishell.h"

void	num_of_files_in_each_part(char **str, t_execution *z)
{
	int	i;
	int	j;
	int	symbol;
	int	size[2];

	j = 0;
	while (str[j] != NULL)
	{
		i = 0;
		size[0] = 0;
		size[1] = 0;
		while (str[j][i] != '\0')
		{
			skip_qut(str[j], &i);
			// printf("8: %c\n", str[j][i]);
			if ((str[j][i] == '<' || str[j][i] == '>') && str[j][i] != '\'' 
				&& str[j][i] != '"')
			{
				symbol = know_symbol(str[j][i]);
				i++;
				if (str[j][i] == '<' || str[j][i] == '>')
				{
					symbol++;
					i++;
				}
				if (str[j][i] == ' ')
					i++;
				if (symbol == 1 || symbol == 2)
					size[0]++;
				else
					size[1]++;
			}
			if (str[j][i] == '\0')
				break ;
			if (str[j][i] != '<' && str[j][i] != '>' && str[j][i] != '\'' 
				&& str[j][i] != '"')
				i++;
		}
		// printf(">>>>>%d, %d\n", size[0], size[1]);
		z->infile_name[j] = malloc(sizeof(char *) * (size[0] + 1));
		z->outfile_name[j] = malloc(sizeof(char *) * (size[1] + 1));
		if (z->infile_name[j] == NULL || z->outfile_name[j] == NULL)
			exit(0);
		j++;
	}
	z->infile_name[j] = NULL;
	// printf("NULL: %d\n", j);
	z->outfile_name[j] = NULL;
}
