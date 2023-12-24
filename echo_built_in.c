/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:30:47 by mahmoud           #+#    #+#             */
/*   Updated: 2023/12/23 17:29:46 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void write_with_line(char **arr, int i)
{
    while (arr[i] != NULL)
    {
        write(1, arr[i], ft_strlen(arr[i]));
        if (arr[i + 1] != NULL)
            write(1, " ", 1);
        i++;
    }
    write(1, "\n", 1);
}

void write_without_line(char **arr, int i)
{
    while (arr[i] != NULL)
    {
        write(1, arr[i], ft_strlen(arr[i]));
        if (arr[i + 1] != NULL)
            write(1, " ", 1);
        i++;
    }
}

void handle_arg_1(char *str)
{
    
}

void echo_built_in(char **arr)
{
    if (arr[0] != NULL)
    {
        if (ft_strncmp(arr[0], "echo", 5) == 0)
        {
            int i;

            if (arr[1] == NULL)
                write(1, "\n", 1);
            else if (arr[1] != NULL && ft_strncmp(arr[1], "-n", 3) != 0)
                write_with_line(arr, 1);
            else if (arr[1] != NULL && ft_strncmp(arr[1], "-n", 3) == 0)
                write_without_line(arr, 2);
        } 
    }
}

int main(void)
{
    char *str;
    char **arr;

    while (1)
    {
         str = readline("line: ");
        arr = ft_split(str, ' ');
        echo_built_in(arr);
    }
}