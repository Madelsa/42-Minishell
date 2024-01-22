#include "../../includes/minishell.h"

void	shift(int i, int j, int skip, t_execution *z)
{
	int	k;

	k = 0;
	while (z->cmds_name[i][j][k + skip + 1] != '\0')
	{
		z->cmds_name[i][j][k + skip] = z->cmds_name[i][j][k + skip + 1];
		k++;
	}
	z->cmds_name[i][j][k + skip] = '\0';
}

static void remove_qut2(t_execution *z, t_vars *v)
{
	if (z->cmds_name[v->i][v->j][v->k] == '\'' && v->qut_symbol == 1)
	{
		v->qut_symbol = 0;
		v->flag = 1;
	}
	else if (z->cmds_name[v->i][v->j][v->k] == '"' && v->qut_symbol == 2)
	{
		v->qut_symbol = 0;
		v->flag = 1;
	}
	else if (z->cmds_name[v->i][v->j][v->k] == '\'' && v->qut_symbol == 0)
	{
		v->qut_symbol = 1;
		v->flag = 1;
	}
	else if (z->cmds_name[v->i][v->j][v->k] == '"' && v->qut_symbol == 0)
	{
		v->qut_symbol = 2;
		v->flag = 1;
	}
	// printf("%c, %s\n", z->cmds_name[v->i][v->j][v->k], z->cmds_name[v->i][v->j]);
	if (v->flag == 1)
		shift(v->i, v->j, v->k, z);
	if (v->flag == 0)
		v->k++;
	v->flag = 0;
}

void	remove_qut(t_execution *z)
{
	t_vars v;

	v.i = 0;
	v.qut_symbol = 0;
	v.flag = 0;
	while (z->cmds_name[v.i] != NULL)
	{
		v.j = 0;
		while (z->cmds_name[v.i][v.j] != NULL)
		{
			v.k = 0;
			while (z->cmds_name[v.i][v.j][v.k] != '\0')
				remove_qut2(z, &v);
			v.j++;
		}
		v.i++;
	}
}

// void	shift_dollar(int skip, char *dollar_str)
// {
// 	int	k;

// 	k = 0;
// 	while (dollar_str[k + skip + 1] != '\0')
// 	{
// 		dollar_str[k + skip] = dollar_str[k + skip + 1];
// 		k++;
// 	}
// 	dollar_str[k + skip] = '\0';
// }

// void	remove_qut_from_dollar(char *dollar_str)
// {
// 	int	k;
// 	int	qut_symbol;
// 	int	flag;

// 	k = 0;
// 	qut_symbol = 0;
// 	flag = 0;
// 	while (dollar_str[k] != '\0')
// 	{
// 		if (dollar_str[k] == '\'' && qut_symbol == 1)
// 		{
// 			qut_symbol = 0;
// 			flag = 1;
// 		}
// 		else if (dollar_str[k] == '"' && qut_symbol == 2)
// 		{
// 			qut_symbol = 0;
// 			flag = 1;
// 		}
// 		else if (dollar_str[k] == '\'' && qut_symbol == 0)
// 		{
// 			qut_symbol = 1;
// 			flag = 1;
// 		}
// 		else if (dollar_str[k] == '"' && qut_symbol == 0)
// 		{
// 			qut_symbol = 2;
// 			flag = 1;
// 		}
// 		if (flag == 1)
// 			shift(k, dollar_str);
// 		if (flag == 0)
// 			k++;
// 		flag = 0;
// 	}
// }
