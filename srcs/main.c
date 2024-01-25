/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:33:26 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/01/25 12:35:57 by aalkaisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse(t_execution *exec, char *str)
{
	char		**res;
	int			i;

	redirections(str, exec);
	res = ft_splitt(str, '|', exec, 1);
	free(str);
	i = -1;
	while (res[++i] != NULL)
		res[i] = ft_strtrimm(res[i], " ");
	many_malloc(exec);
	num_of_files_in_each_part(res, exec);
	num_of_chars_in_each_file(res, exec);
	put_chars_in_each_file(res, exec);
	put_commands(res, exec);
	i = -1;
	while (res[++i] != NULL)
		free(res[i]);
	free(res);
	remove_qut(exec);
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
		signal(SIGINT, is_parent_child_sig);
		signal(SIGQUIT, is_parent_child_sig);
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
		if (check_qut_error(str) == 1)
			continue ;
		str = dollar(str, dictionary, exec);
		tab_to_space(str);
		if (skip_spaces(str) == 1)
			continue ;
		str = ft_strtrim_all(str);
		if (str == NULL)
			continue ;
		if (find_syntax_error(str, exec) == 1)
			continue ;
		parse(exec, str);
		handle_out_file(exec);
		handle_in_file(exec, dictionary);
		check_func_path_acess(exec, &dictionary);
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
			waitpid(exec->process_id[i], &status, 0);
			if (WIFEXITED(status))
				exec->exit_code = status;
		}
		unlink_func(exec);
		free_all(exec);
	}
}


int main (int ac, char **av, char **envp)
{
	t_execution exec;
	t_dict *dictionary = NULL;

	fill_dictionary(envp, &dictionary);
	(void)ac;
	(void)av;
	prompt(&exec, dictionary);
}
