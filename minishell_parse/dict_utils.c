/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 15:07:28 by mahmoud           #+#    #+#             */
/*   Updated: 2023/12/26 14:17:13 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_dict_lstsize(t_dict *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_dict_lstdelone(t_dict *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->key);
    del(lst->value);
	free(lst);
}

void	ft_dict_lstclear(t_dict **lst, void (*del)(void *))
{
	t_dict	*node;
	t_dict	*next;

	if (!lst || !*lst || !del)
		return ;
	node = *lst;
	while (node)
	{
		next = node->next;
		free(node);
		node = next;
	}
	*lst = NULL;
}

void	ft_dict_lstadd_back(t_dict **lst, t_dict *new)
{
	t_dict	*node;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	node = *lst;
	while (node->next)
		node = node->next;
	node->next = new;
}

t_dict *ft_dict_lstnew(char *key, char *value) {
    t_dict *node = (t_dict *)malloc(sizeof(t_dict));
    if (!node)
        return NULL;

    node->key = NULL;
    node->value = NULL;

    if (key) {
        node->key = ft_strdup(key);
        if (!node->key) {
            free(node);
            return NULL;
        }
    }

    if (value) {
        node->value = ft_strdup(value);
        if (!node->value) {
            free(node->key);
            free(node);
            return NULL;
        }
    }

    node->next = NULL;
    return node;
}
