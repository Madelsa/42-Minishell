#include "../../includes/minishell.h"

int	size_after_trim(char *str)
{
	int		i;
	int		size;
	char	flag;
	int		qut_num[2];

	i = 0;
	size = 0;
	flag = 'N';
	qut_num[0] = 0;
	qut_num[1] = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] != '\0' && flag == 'Y')
			size++;
		while (inside_qut(str, i, qut_num, 1) == 1 || 
			(str[i] != ' ' && str[i] != '\0'))
		{
			size++;
			i++;
			flag = 'Y';
		}
	}
	// printf("4>size: %d\n", size);
	return (size);
}

void	ft_strtrim2(char *res, char *str, int size)
{
	int		i;
	char	flag;
	int		qut_num[2];

	i = 0;
	flag = 'N';
	qut_num[0] = 0;
	qut_num[1] = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] != '\0' && flag == 'Y')
		{
			res[size] = ' ';
			size++;
		}
		while (inside_qut(str, i, qut_num, 1) == 1 || 
			(str[i] != ' ' && str[i] != '\0'))
		{
			res[size] = str[i];
			size++;
			i++;
			flag = 'Y';
		}
	}
	// printf("--->%s\n", str);
	free(str);
	res[size] = '\0';
}

char	*ft_strtrim_all(char *str)
{
	int		size;
	char	*res;

	if (str == NULL)
		return (NULL);
	size = size_after_trim(str);
	res = (char *)malloc(size + 1);
	if (res == NULL)
		return (NULL);
	size = 0;
	ft_strtrim2(res, str, size);
	return (res);
}
