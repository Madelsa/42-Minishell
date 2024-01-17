#include "../../includes/minishell.h"

static void num_of_chars_in_each_file2(char **str, t_vars *v)
{
	if (str[v->j][v->i] == '<' || str[v->j][v->i] == '>')
	{
		v->symbol++;
		v->i++;
	}
	if (str[v->j][v->i] == ' ')
		v->i++;
	v->num_of_chars = 0;
	while (inside_qut(str[v->j], v->i, v->qut_num, 1) == 1 || (inside_qut(str[v->j]
				, v->i, v->qut_num, 2) == 0 && str[v->j][v->i] != ' ' && 
		str[v->j][v->i] != '<' && str[v->j][v->i] != '>' && str[v->j][v->i] != '\0'))
	{
		// printf("1>>>%c, %v->i, %i\n", str[v->j][v->i], v->i, inside_qut(str[v->j], v->i, v->qut_num, 2));
		if (inside_qut(str[v->j], v->i, v->qut_num, 2) == 1 && (str[v->j][v->i] == '\'' || \
			str[v->j][v->i] == '"') && (v->qut_symbol == str[v->j][v->i] || v->qut_symbol == 'N'))
			v->qut_symbol = str[v->j][v->i];
		else if (inside_qut(str[v->j], v->i, v->qut_num, 2) == 0 && v->qut_symbol == str[v->j][v->i])
			v->qut_symbol = 'N';
		else
			v->num_of_chars++;
		v->i++;
	}
}

static int num_of_chars_in_each_file3(char **str, t_execution *z, t_vars *v)
{
	if (inside_qut(str[v->j], v->i, v->qut_num, 1) == 0 && 
		(str[v->j][v->i] == '<' || str[v->j][v->i] == '>'))
	{
		v->symbol = know_symbol(str[v->j][v->i]);
		v->i++;
		num_of_chars_in_each_file2(str, v);
		printf("---------------------------------------------- %d, %d\n", v->num_of_chars, v->j);
		if (v->symbol == 1 || v->symbol == 2)
			z->infile_name[v->j][v->size[0]] = malloc(v->num_of_chars + 1);
		else
			z->outfile_name[v->j][v->size[1]] = malloc(v->num_of_chars + 1);
		if (v->symbol == 1 || v->symbol == 2)
			v->size[0]++;
		else
			v->size[1]++;
		printf("v->num_of_chars: %d\n", v->num_of_chars);
	}
	if (inside_qut(str[v->j], v->i, v->qut_num, 2) == 1 || (str[v->j][v->i] != '<' && str[v->j][v->i] != '>' && str[v->j][v->i] != '\0'))
		v->i++;
	if (str[v->j][v->i] == '\0')
		return (1);
	// printf("%d\n", v->i);
	return (0);
}

void	num_of_chars_in_each_file(char **str, t_execution *z)
{
	t_vars v;

	v.j = 0;
	v.qut_num[0] = 0;
	v.qut_num[1] = 0;
	v.qut_symbol = 'N';
	while (str[v.j] != NULL)
	{
		v.i = 0;
		v.size[0] = 0;
		v.size[1] = 0;
		while (str[v.j][v.i] != '\0')
		{
			if(num_of_chars_in_each_file3(str, z, &v))
				continue ;
		}
		z->infile_name[v.j][v.size[0]] = NULL;
		z->outfile_name[v.j][v.size[1]] = NULL;
		// printf("z->infile_name[%d][%d] = %s\n", v.j, v.size[0], z->infile_name[v.j][v.size[0]]);
		// printf("z->outfile_name[%d][%d] = %s\n", v.j, v.size[1], z->outfile_name[v.j][v.size[1]]);
		v.j++;
	}
	// printf("?????????????????????????\n");
}