/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:33:26 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/01/28 00:21:58 by mahmoud          ###   ########.fr       */
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

void	prompt3(t_execution *exec)
{
	int	flag;
	int	status;
	int	i;

	open_heredoc_files(exec);
	open_pipes(exec);
	flag = create_children(exec);
	if (flag == 0)
		close_all_fds(exec);
	i = -1;
	while (exec->cmds_name[++i] != NULL && flag == 0)
	{
		waitpid(exec->process_id[i], &status, 0);
		if (WIFEXITED(status))
			exec->exit_code = WEXITSTATUS(status);
	}
	g_signal = 1;
	unlink_func(exec);
	free_all(exec);
}

int	prompt2(t_execution *exec, char *rl, char *str)
{
	if (rl[0] == '\0')
		return ((1));
	add_history(rl);
	str = ft_strdup(rl);
	if (check_qut_error(str) == 1)
		return ((1));
	str = dollar(str, exec);
	tab_to_space(str);
	if (skip_spaces(str) == 1)
		return ((1));
	str = ft_strtrim_all(str);
	if (str == NULL)
		return ((1));
	if (find_syntax_error(str, exec) == 1)
		return ((1));
	parse(exec, str);
	handle_out_file(exec);
	handle_in_file(exec);
	check_func_path_acess(exec);
	if (g_signal != 1)
	{
		free_all(exec);
		return ((1));
	}
	return (0);
}

void	prompt(t_execution *exec)
{
	char	*str;
	char	*rl;

	str = NULL;
	// dictionary = NULL;
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
			return (printf("exit\n"), ft_dict_lstclear(&exec->dictionary, free),
				 exit(0));
		}
		if (prompt2(exec, rl, str) == 1)
			continue ;
		prompt3(exec);
	}
}

int		g_signal = 0;


int	main(int ac, char **av, char **envp)
{
	t_execution	exec;
	// t_dict		*dictionary;

	// dictionary = NULL;
	exec.dictionary = NULL;
	fill_dictionary(envp, &exec);
	(void)ac;
	(void)av;
	prompt(&exec);
}
