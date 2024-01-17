/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:59:53 by mohammoh          #+#    #+#             */
/*   Updated: 2024/01/15 17:13:05 by mabdelsa         ###   ########.fr       */
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
	value = NULL;
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
				value = NULL;
				break;
			}
			i++;
		}
		if (value == NULL)
			str = ft_strjoin3(str1, value2, str2);
		else
			str = ft_strjoin3(str1, value, str2);
		if (value != NULL)
			free(value);
		if (value2 != NULL)
			free(value2);
		free(dollar_word);
	}
	return (free(str1), free(str2), str);
}

char	*subsitute_exit_code(char *str, int i)
{
	char	*str1;
	char	*str2;
	char	*str3;
	
	str1 = ft_substr(str, 0, i - 1);
	str2 = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	free(str);
	str3 = ft_itoa(g_exit_code);
	str = ft_strjoin3(str1, str3, str2);
	return (free(str1), free(str2), free(str3), str);
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
			if (str[i] == '?')
			{
				str = subsitute_exit_code(str, i);
				continue ;
			}
			j = 0;
			hash_flag = 0;
			while ((str[j + i] == '_' || ft_isalnum(str[j + i]) == 1))
				j++;
			if (str[i] == '#')
				str[i] = '0';
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
			// printf("str: %s,\n", str);
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

void	unlink_func(t_execution *exec)
{
	int		i;
	char	*heredoc_file;

	i = -1;
	while (exec->full_path[++i] != NULL)
	{
		heredoc_file = heredoc_file_name("/tmp/here_doc_", i, ".tmp");
		if (access(heredoc_file, F_OK) == 0)
		{
			unlink(heredoc_file);
		}
	}
}

void	free_all(t_execution *exec)
{
	int i = 0;
	int j = 0;
	// ft_putstr_fd()
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
	i = 0;
	while (exec->full_path[i] != NULL)
	{
		free(exec->full_path[i]);
		i++;
	}
	free(exec->full_path);
	i = 0;
	while (i < exec->cmds_num - 1)
	{
		free(exec->fd_pipe[i]);
		i++;
	}
	free(exec->fd_pipe);
	free(exec->process_id);
	free(exec->in_file_error);
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
	many_malloc(exec);
	// printf("%s, %s.\n", res[0], res[1]);
	// printf("11111.\n");
	num_of_files_in_each_part(res, exec);
	num_of_chars_in_each_file(res, exec);
	put_chars_in_each_file(res, exec);
	put_commands(res, exec);
	i = -1;
	while (res[++i] != NULL)
		free(res[i]);
	free(res);
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

int g_exit_code = 0;

int main (int ac, char **av, char **envp)
{
	t_execution exec;
	char		*str;
	char		*rl;
	int			i;
	int			flag;
	int			status;
	// int			std_in;
	// int			std_out;
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
		// printf("TEST_7\n");
		parse(&exec, str);
		// printf("TEST_7\n");
		// check_func_path_acess(envp,  &exec);
		////////////
		// char **cmd = *exec.cmds_name;
		// search_command_builtins(cmd, &dictionary);
		handle_out_file(&exec);
		handle_in_file(&exec, dictionary);
		open_heredoc_files(&exec);
		check_func_path_acess(envp, &exec);
		open_pipes( &exec);
		flag = create_children(envp, &exec, &dictionary);
		if (flag == 0)
			close_all_fds(&exec, 1);
		i = -1;
		while (exec.full_path[++i] != NULL && flag == 0)
		{
			// waitpid(exec.process_id[i], &status[0], 0);
			// printf("HERE %i\n", i);
			waitpid(exec.process_id[i], &status, 0);
			if (WIFEXITED(status))
				g_exit_code = status;
			// if (status[0] != 0)
			// 	status[1] = 1;
			// printf("HERE %i\n", i);
		}
		printf("exit code: %d\n", g_exit_code);
		unlink_func(&exec);
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
