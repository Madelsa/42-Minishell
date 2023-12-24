/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:09:09 by mahmoud           #+#    #+#             */
/*   Updated: 2023/12/23 17:12:51 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void print_directory(void)
{
    char *directory;

    directory = NULL;
    directory = getcwd(directory, 0);
    if (directory == NULL)
    {
        ft_putstr_fd("Error: cannot retrieve current directory\n", 2);
        return ;
    }
    write(1, directory, ft_strlen(directory));
    write(1, "\n", 1);
    free(directory);
}

void pwd_built_in(char **arr)
{
   if (arr[0] != NULL)
   {
        if (ft_strncmp(arr[0], "pwd", 4) == 0)
        {
            if (arr[1] != NULL)
            {
                if ((arr[1][0] == '\"' && arr[1][1] == '-' || arr[1][0] == '\'' && arr[1][1] == '-')
                    || arr[1][0] == '-')
                    ft_putstr_fd("Error: invalid option\n", 2);
                else
                    print_directory();
            }
            else
                print_directory();
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
        pwd_built_in(arr);
    }
}