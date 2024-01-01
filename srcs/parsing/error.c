#include "../../includes/minishell.h"

int	double_pipe_error(char *str)
{
	int	i;
	int	symbol;
	int	qut_num[2];

	i = 0;
	symbol = 0;
	qut_num[0] = 0;
	qut_num[1] = 0;
	while (str[i] != '\0')
	{
		if (inside_qut(str, i, qut_num, 1) == 0)
		{
			if (str[i] == '|' && symbol == 1)
				return (1);
			if (str[i] != ' ' && symbol == 1)
				symbol = 0;
			if (str[i] == '|' && symbol == 0)
				symbol = 1;
		}
		i++;
	}
	return (0);
}

int	double_symbol_error(char *str)
{
	int	i;
	int	symbol;
	int	qut_num[2];

	i = 0;
	symbol = 0;
	qut_num[0] = 0;
	qut_num[1] = 0;
	while (str[i] != '\0')
	{
		if (inside_qut(str, i, qut_num, 1) == 0 && str[i] == '<' && symbol == 0)
		{
			i++;
			if (inside_qut(str, i, qut_num, 1) == 0 && str[i] == '<')
			{
				symbol = 2;
				i++;
			}
			else
				symbol = 1;
		}
		else if (inside_qut(str, i, qut_num, 2) == 0 && str[i] == '>' && symbol == 0)
		{
			i++;
			if (inside_qut(str, i, qut_num, 1) == 0 && str[i] == '>')
			{
				symbol = 4;
				i++;
			}
			else
				symbol = 3;
		}
		else if (inside_qut(str, i, qut_num, 2) == 0 && (str[i] == '|' || 
				str[i] == '<' || str[i] == '>') && symbol != 0)
		{
			printf("bash: syntax error near unexpected token `%c'\n", str[i]);
			return (1);
		}
		if (str[i] != ' ' && str[i] != '<' && str[i] != '>' && str[i] != '|')
			symbol = 0;
		i++;
	}
	return (0);
}

int	find_syntax_error(char	*str)
{
	int	i;

	i = 0;
	if (str[0] == '|' || str[ft_strlen(str) - 1] == '|' || 
		str[ft_strlen(str) - 1] == '<' || 
		str[ft_strlen(str) - 1] == '>')
	{
		write(2, "Error\n", 6);
		free(str);
		return (1);
	}
	if (double_pipe_error(str) == 1 || double_symbol_error(str) == 1)
	{
		write(2, "Error\n", 6);
		free(str);
		return (1);
	}
	return (0);
}
