/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:33:26 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/01/25 10:05:04 by aalkaisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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



void	unlink_func(t_execution *exec)
{
	int		i;
	char	*heredoc_file;

	i = -1;
	while (exec->cmds_name[++i] != NULL)
	{
		heredoc_file = heredoc_file_name("/tmp/here_doc_", i, ".txt");
		if (access(heredoc_file, F_OK) == 0)
		{
			unlink(heredoc_file);
		}
		free(heredoc_file);
	}
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
	if (exec->full_path != NULL)
	{
		// printf("%s\n", exec->cmds_name[0][0]);
		i = 0;
		while (exec->cmds_name[i] != NULL)
		{
			if (exec->full_path[i] != NULL)
				free(exec->full_path[i]);
			i++;
		}
		free(exec->full_path);
	}
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
	while (i < exec->cmds_num - 1)
	{
		free(exec->fd_pipe[i]);
		i++;
	}
	i = 0;
	if (exec->paths != NULL)
	{
		while (exec->paths[i] != NULL)
		{
			free(exec->paths[i]);
			i++;
		}
		free(exec->paths);
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

int g_signal = 0;

void prompt(t_execution *exec, t_dict *dictionary)
{
	char		*str;
	char		*rl;
	int			i;
	int			flag;
	int			status;

	while (1)
	{
		// exec.full_path = NULL;
		signal(SIGINT, is_parent_child_sig);
		signal(SIGQUIT, is_parent_child_sig);

		// exec->full_path = NULL;
		// exec->paths = NULL;
		// exec.exit_code = g_signal;
		// printf("sig: %d\n", g_signal);
		if (g_signal != 1)
			exec->exit_code = g_signal;
		g_signal = 1;
		rl = readline("minishell$ ");
		if (g_signal == 99)
			exec->exit_code = 1;
		g_signal = 1;
		if (rl == NULL)
		{
			printf("exit\n");
			ft_dict_lstclear(&dictionary, free);
			// rl_clear_history();
			exit(0);
		}
		if (rl[0] == '\0')
			continue ;
		add_history(rl);
		str = ft_strdup(rl);
		// dollar(str);
		// if (str_cmp(str, "exit") == 1)
		// 	break ;
		// printf("lol--->%s.\n", str);
		if (check_qut_error(str) == 1)
			continue ;
		str = dollar(str, dictionary, exec);
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
		if (find_syntax_error(str, exec) == 1)
			continue ;
		// printf("TEST_7\n");
		parse(exec, str);
		// printf("TEST_7\n");
		// check_func_path_acess(envp,  &exec);
		////////////
		// char **cmd = *exec.cmds_name;
		// search_command_builtins(cmd, dictionary);
		handle_out_file(exec);
		handle_in_file(exec, dictionary);
		check_func_path_acess(exec, &dictionary);
		// printf("sig: %d\n", g_signal);
		if (g_signal != 1)
		{
			free_all(exec);
			continue ;
		}
		open_heredoc_files(exec);
		open_pipes(exec, &dictionary);
		flag = create_children(exec, &dictionary);
		if (flag == 0)
			close_all_fds(exec);
		i = -1;
		while (exec->cmds_name[++i] != NULL && flag == 0)
		{
			// waitpid(exec.process_id[i], &status[0], 0);
			// printf("HERE %i\n", i);
			waitpid(exec->process_id[i], &status, 0);
			if (WIFEXITED(status))
				exec->exit_code = status;
			// if (status[0] != 0)
			// 	status[1] = 1;
			// printf("HERE %i\n", i);
		}
		// printf("exit code: %d\n", exec.exit_code);
		unlink_func(exec);
		// if (str_cmp("here_doc", argv[1], 0))
		// 	unlink("here_doc");
		/////////////
		// printf("%d\n", 42);
		// redir_and_exec(&exec);
		// ft_dict_lstclear(dictionary, free);
		free_all(exec);
	}
}


int main (int ac, char **av, char **envp)
{
	t_execution exec;
	// char		*str;
	// char		*rl;
	// int			i;
	// int			flag;
	// int			status;
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
	prompt(&exec, dictionary);
	// while (1)
	// {
	// 	// exec.full_path = NULL;
	// 	signal(SIGINT, is_parent_child_sig);
	// 	signal(SIGQUIT, is_parent_child_sig);
	// 	// exec.exit_code = g_signal;
	// 	if (g_signal != 1)
	// 		exec.exit_code = g_signal;
	// 	g_signal = 1;
	// 	rl = readline("minishell$ ");
	// 	if (rl == NULL)
	// 	{
	// 		printf("exit\n");
	// 		exit(0);
	// 	}
	// 	if (rl[0] == '\0')
	// 		continue ;
	// 	add_history(rl);
	// 	str = ft_strdup(rl);
	// 	// dollar(str);
	// 	// if (str_cmp(str, "exit") == 1)
	// 	// 	break ;
	// 	// printf("lol--->%s.\n", str);
	// 	if (check_qut_error(str) == 1)
	// 		continue ;
	// 	str = dollar(str, dictionary, &exec);
	// 	// printf("1--->%s.\n", str);
	// 	tab_to_space(str);
	// 	if (skip_spaces(str) == 1)
	// 		continue ;
	// 	// printf("2--->%s.\n", str);
	// 	// printf("3--->%zu.\n", ft_strlen(str));
	// 	str = ft_strtrim_all(str);
	// 	// printf("--->%s.%d\n", str, ft_strlen(str));
	// 	if (str == NULL)
	// 		continue ;
	// 	// printf("11111.\n");
	// 	if (find_syntax_error(str, &exec) == 1)
	// 		continue ;
	// 	// printf("TEST_7\n");
	// 	parse(&exec, str);
	// 	// printf("TEST_7\n");
	// 	// check_func_path_acess(envp,  &exec);
	// 	////////////
	// 	// char **cmd = *exec.cmds_name;
	// 	// search_command_builtins(cmd, &dictionary);
	// 	handle_out_file(&exec);
	// 	handle_in_file(&exec, dictionary);
	// 	check_func_path_acess(&exec, &dictionary);
	// 	if (g_signal != 1)
	// 	{
	// 		free_all(&exec);
	// 		continue ;
	// 	}
	// 	open_heredoc_files(&exec);
	// 	open_pipes( &exec);
	// 	flag = create_children(&exec, &dictionary);
	// 	if (flag == 0)
	// 		close_all_fds(&exec, 1);
	// 	i = -1;
	// 	while (exec.full_path[++i] != NULL && flag == 0)
	// 	{
	// 		// waitpid(exec.process_id[i], &status[0], 0);
	// 		// printf("HERE %i\n", i);
	// 		waitpid(exec.process_id[i], &status, 0);
	// 		if (WIFEXITED(status))
	// 			exec.exit_code = status;
	// 		// if (status[0] != 0)
	// 		// 	status[1] = 1;
	// 		// printf("HERE %i\n", i);
	// 	}
	// 	// printf("exit code: %d\n", exec.exit_code);
	// 	unlink_func(&exec);
	// 	// if (str_cmp("here_doc", argv[1], 0))
	// 	// 	unlink("here_doc");
	// 	/////////////
	// 	// printf("%d\n", 42);
	// 	// redir_and_exec(&exec);
	// 	free_all(&exec);
	// }
	
	//redir and execute
	//filled struct
	//if it true then start executing
}
