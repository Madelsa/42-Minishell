/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:59:53 by mohammoh          #+#    #+#             */
/*   Updated: 2024/01/05 18:48:37 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// #include "../srcs/parsing/minishell_parse.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	int		i[3];
	char	*res;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (s1 == NULL || s2 == NULL || s3 == NULL)
		return (NULL);
	i[0] = ft_strlen(s1);
	i[1] = ft_strlen(s2);
	i[2] = ft_strlen(s3);
	res = malloc(i[0] + i[1] + i[2] + 1);
	if (res == NULL)
		return (NULL);
	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	while (s1[++i[0]] != '\0')
		res[i[0]] = s1[i[0]];
	while (s2[++i[1]] != '\0')
		res[i[0] + i[1]] = s2[i[1]];
	while (s3[++i[2]] != '\0')
		res[i[0] + i[1] + i[2]] = s3[i[2]];
	res[i[0] + i[1] + i[2]] = '\0';
	return (res);
}

char	*find_value_from_key(char	*key, t_dict *dictionary)
{
	char	*value;

	value = NULL;
	while (dictionary != NULL)
	{
		if (ft_strcmp(dictionary->key, key) == 0)
		{
			value = ft_strdup(dictionary->value);
		}
		dictionary = dictionary->next;
	}
	if (value == NULL)
		value = ft_strdup("");
	return (value);
}


char	*ft_replace(char *str, char *dollar_word, int i, int j, t_dict *dictionary, int is_value, int is_double_qut)
{
	char	*str1;
	char	*str2;
	char	*value;
	char	*value2;

	value2 = NULL;
	str1 = ft_substr(str, 0, i);
	str2 = ft_substr(str, i + j + 1, ft_strlen(str) - i - j - 1);
	free(str);
	if (is_value == 0)
		str = ft_strjoin(str1, str2);
	else
	{
		value = find_value_from_key(dollar_word, dictionary);
		i = 0;
		while (value[i] != '\0')
		{
			if ((value[i] == '<' || value[i] == '>' || value[i] == '|') && is_double_qut == 0)
			{
				value2 = ft_strjoin3("\"", value, "\"");
				free(value);
				break;
			}
			i++;
		}
		str = ft_strjoin3(str1, value2, str2);
		free(value2);
		free(dollar_word);
	}
	return (free(str1), free(str2), str);
}

char	*dollar(char *str, t_dict *dictionary)
{
	int		i;
	int		j;
	int		hash_flag;
	int		qut_num[2];
	char	*dollar_word;
	int		del_dollar_flag;

	i = 0;
	qut_num[0] = 0;
	qut_num[1] = 0;
	while (str[i] != '\0')
	{
		del_dollar_flag = 0;
		if ((inside_single_or_double_qut(str, i, qut_num, 1) == 2 && str[i] == '$') || 
		(inside_single_or_double_qut(str, i, qut_num, 2) == 0 && str[i] == '$'))
		{
			del_dollar_flag = 2;
			i++;
			j = 0;
			hash_flag = 0;
			while ((str[j + i] == '_' || ft_isalnum(str[j + i]) == 1))
				j++;
			if (str[i] == '#')
			{
				str[i] = '0';
			}
			if ((str[i] == '\'' || str[i] == '"') && inside_single_or_double_qut(str, i, qut_num, 2) == 0)
			{
				str[i - 1] = ' ';
				del_dollar_flag = 1;
			}
			else if (str[i] == ' ' || str[i] == '\'' || str[i] == '"' || str[i] == '\0')
			{
				continue ;
			}
			else
			{
				if (j == 0)
				{
					str = ft_replace(str, "", i - 1, j, dictionary, 0, 0);
					del_dollar_flag = 1;
				}
				else if (str[i] >= '0' && str[i] <= '9' && hash_flag == 0)
				{
					str = ft_replace(str, "", i - 1, 1, dictionary, 0, 0);
					del_dollar_flag = 1;
				}
				else
				{
					del_dollar_flag = 1;
					dollar_word = ft_substr(str, i, j);
					str = ft_replace(str, dollar_word, i - 1, j, dictionary, 1, inside_single_or_double_qut(str, i, qut_num, 2));
				}
			}
			printf("str: %s,\n", str);
		}
		if (del_dollar_flag == 1)
		{
			i = i - 2;
			if (i < 0)
				i = 0;
		}
		else if (del_dollar_flag == 2)
			i--;
		i++;
	}
	return (str);
}

void	free_all(t_execution *exec)
{
	int i = 0;
	int j = 0;

	while (exec->infile_name[i] != NULL)
	{
		j = 0;
		while (exec->infile_name[i][j] != NULL)
		{
			free(exec->infile_name[i][j]);
			j++;
		}
		free(exec->infile_name[i]);
		i++;
	}
	free(exec->infile_name);
	i = 0;
	j = 0;
	while (exec->outfile_name[i] != NULL)
	{
		j = 0;
		while (exec->outfile_name[i][j] != NULL)
		{
			free(exec->outfile_name[i][j]);
			j++;
		}
		free(exec->outfile_name[i]);
		i++;
	}
	free(exec->outfile_name);
	i = 0;
	free(exec->is_file_or_here_doc);
	free(exec->is_file_or_append);
	i = 0;
	j = 0;
	while (exec->cmds_name[i] != NULL)
	{
		j = 0;
		while (exec->cmds_name[i][j] != NULL)
		{
			free(exec->cmds_name[i][j]);
			j++;
		}
		free(exec->cmds_name[i]);
		i++;
	}
	free(exec->cmds_name);
	free(exec->fd_infile);
	free(exec->fd_outfile);
}

void	parse(t_execution *exec, char *str)
{
	char		**res;
	int			i;
	// char		*dollar_var;
	// char		*dollar_value;

	// printf("%s...\n", str);
	// printf("11111.\n");
	redirections(str, exec);
	// // printf("%s..\n", str);
	// printf("11111.\n");
	res = ft_splitt(str, '|', exec, 1);
	free(str);
	// printf("77777.\n");
	i = -1;
	while (res[++i] != NULL)
		res[i] = ft_strtrimm(res[i], " ");
	printf("TEST_8\n");
	many_malloc(exec);
	printf("TEST_8\n");
	// printf("%s, %s.\n", res[0], res[1]);
	// printf("11111.\n");
	num_of_files_in_each_part(res, exec);
	printf("11111.\n");
	num_of_chars_in_each_file(res, exec);
	printf("11111.\n");
	put_chars_in_each_file(res, exec);
	printf("TEST_9\n");
	put_commands(res, exec);
	i = -1;
	while (res[++i] != NULL)
		free(res[i]);
	free(res);
	printf("TEST_9\n");
	remove_qut(exec);
	check_solution(exec);

	// free_all(exec);
	// re_order(res, &z);
}
int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '\0')
		return(1);
	return(0);
}

int main (int ac, char **av, char **envp)
{
	t_execution exec;
	char		*str;
	char		*rl;
	int			i;
	///////////
	t_dict *dictionary = NULL;
	fill_dictionary(envp, &dictionary);
	(void)ac;
	(void)av;
	///////////
	//parent the rest is children
	//while loop that doesnt break untill theres a signal to quit the loop
	//to check the initaite the env and fill struct 
	//heredoc will always be the first to be executed
	//all the commands will be executed toghter
	// check the arugments if its valid	
	////////////////////
	////////////////////
	while (1)
	{
		rl = readline("minishell$ ");
		if (rl == NULL || rl[0] == '\0')
			continue ;
		add_history(rl);
		str = ft_strdup(rl);
		// dollar(str);
		// if (str_cmp(str, "exit") == 1)
		// 	break ;
		// printf("lol--->%s.\n", str);
		if (check_qut_error(str) == 1)
			continue ;
		str = dollar(str, dictionary);
		// printf("1--->%s.\n", str);
		tab_to_space(str);
		if (skip_spaces(str) == 1)
			continue ;
		// printf("2--->%s.\n", str);
		// printf("3--->%zu.\n", ft_strlen(str));
		str = ft_strtrim_all(str);
		// printf("--->%s.%d\n", str, ft_strlen(str));
		if (str == NULL)
			continue ;
		// printf("11111.\n");
		if (find_syntax_error(str) == 1)
			continue ;
		printf("TEST_7\n");
		parse(&exec, str);
		printf("TEST_7\n");
		// check_func_path_acess(envp,  &exec);
		////////////
		char **cmd = *exec.cmds_name;
		search_command_builtins(cmd, &dictionary);
		handle_out_file(&exec);
		handle_in_file(&exec);
		open_heredoc_files(&exec);
		check_func_path_acess(envp, &exec);
		open_pipes( &exec);
		create_children(envp, &exec);
		i = -1;
		while (exec.full_path[++i])
		{
			// waitpid(exec.process_id[i], &status[0], 0);
			waitpid(exec.process_id[i], &g_exit_code, 0);
			// if (status[0] != 0)
			// 	status[1] = 1;
		}
		close_all_fds(&exec, 1);
		// if (str_cmp("here_doc", argv[1], 0))
		// 	unlink("here_doc");
		/////////////
		// printf("%d\n", 42);
		// redir_and_exec(&exec);
		free_all(&exec);
	}
	//redir and execute
	//filled struct
	//if it true then start executing
}
