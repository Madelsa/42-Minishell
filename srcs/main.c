/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:59:53 by mohammoh          #+#    #+#             */
/*   Updated: 2024/01/03 13:40:37 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// #include "../srcs/parsing/minishell_parse.h"

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
	res = ft_splitt(str, '|', exec);
	free(str);
	// printf("77777.\n");
	i = -1;
	while (res[++i] != NULL)
		res[i] = ft_strtrimm(res[i], " ");
	many_malloc(exec);
	// printf("%s, %s.\n", res[0], res[1]);
	// printf("11111.\n");
	num_of_files_in_each_part(res, exec);
	// printf("11111.\n");
	num_of_chars_in_each_file(res, exec);
	// printf("11111.\n");
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


int main (int ac, char **av, char **envp)
{
	t_execution exec;
	char		*str;
	char		*rl;
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
		// printf("1--->%s.\n", str);
		tab_to_space(str);
		// printf("2--->%s.\n", str);
		// printf("3--->%zu.\n", ft_strlen(str));
		str = ft_strtrim_all(str);
		// printf("--->%s.%d\n", str, ft_strlen(str));
		if (str == NULL)
			continue ;
		// printf("11111.\n");
		if (find_syntax_error(str) == 1)
			continue ;
		parse(&exec, str);
		////////////
		char **cmd = *exec.cmds_name;
		search_command_builtins(cmd, &dictionary);
		handle_out_file(&exec);
		// echo_built_in(cmd);
		// pwd_built_in(cmd);
		// exit_built_in(cmd);
		// env_built_in(cmd, &dictionary);
		// export_built_in(cmd, &dictionary);
		// unset_built_in(cmd, &dictionary);
		// cd_built_in(cmd, &dictionary);
		/////////////
		// printf("%d\n", 42);
		// redir_and_exec(&exec);
		free_all(&exec);
	}
	//redir and execute
	//filled struct
	//if it true then start executing
}