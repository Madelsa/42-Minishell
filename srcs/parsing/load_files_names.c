#include "../../includes/minishell.h"

static void put_chars_in_each_file2(t_vars *v, char **str, t_execution *z)
{
	while (inside_qut(str[v->j], v->i, v->qut_num, 1) == 1 || (inside_qut(str[v->j]
				, v->i, v->qut_num, 2) == 0 && str[v->j][v->i] != ' ' && 
		str[v->j][v->i] != '<' && str[v->j][v->i] != '>' && str[v->j][v->i] != '\0'))
	{
		if (inside_qut(str[v->j], v->i, v->qut_num, 2) == 1 && (str[v->j][v->i] == '\'' || \
			str[v->j][v->i] == '"') && (v->qut_symbol == str[v->j][v->i] || v->qut_symbol == 'N'))
		{
			v->qut_symbol = str[v->j][v->i];
			str[v->j][v->i] = ' ';
		}
		else if (inside_qut(str[v->j], v->i, v->qut_num, 2) == 0 && v->qut_symbol == str[v->j][v->i])
		{
			v->qut_symbol = 'N';
			str[v->j][v->i] = ' ';
		}
		else
		{
			if (v->symbol == 1 || v->symbol == 2)
				z->infile_name[v->j][v->size[0]][v->num_of_chars] = str[v->j][v->i];
			else
				z->outfile_name[v->j][v->size[1]][v->num_of_chars] = str[v->j][v->i];
			v->num_of_chars++;
			str[v->j][v->i] = ' ';
		}
		v->i++;
	}
}

static void put_chars_in_each_file3(t_vars *v, char **str, t_execution *z)
{
	if (inside_qut(str[v->j], v->i, v->qut_num, 1) == 0 && 
		(str[v->j][v->i] == '<' || str[v->j][v->i] == '>'))
	{
		v->symbol = know_symbol(str[v->j][v->i]);
		str[v->j][v->i] = ' ';
		v->i++;
		if (str[v->j][v->i] == '<' || str[v->j][v->i] == '>')
		{
			v->symbol++;
			str[v->j][v->i] = ' ';
			v->i++;
		}
		if (str[v->j][v->i] == ' ')
			v->i++;
		v->num_of_chars = 0;
		put_chars_in_each_file2(v, str, z);
		if (v->symbol == 1 || v->symbol == 2)
			z->infile_name[v->j][v->size[0]][v->num_of_chars] = '\0';
		else
			z->outfile_name[v->j][v->size[1]][v->num_of_chars] = '\0';
		// if (v->symbol == 1 || v->symbol == 2)
			// printf("111 %s\n", z->infile_name[v->j][v->size[0]]);
		// else
			// printf("222 %s\n", z->outfile_name[v->j][v->size[1]]);
		if (v->symbol == 1 || v->symbol == 2)
			v->size[0]++;
		else
			v->size[1]++;
	}
}

void	put_chars_in_each_file(char **str, t_execution *z)
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
			// printf("i: %i\n", v.i);
			put_chars_in_each_file3(&v, str, z);
			if (inside_qut(str[v.j], v.i, v.qut_num, 2) == 1 || \
				(str[v.j][v.i] != '<' && str[v.j][v.i] != '>' && str[v.j][v.i] != '\0'))
				v.i++;
			if (str[v.j][v.i] == '\0')
				continue ;
		}
		// printf("-------------------------------------%s\n", str[v.j]);
		v.j++;
	}
}
