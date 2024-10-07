/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:04:01 by tursescu          #+#    #+#             */
/*   Updated: 2024/09/30 15:53:41 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_env   *create_env(char *value)
{
    t_env   *new;

    new = malloc(sizeof(t_env));
    if (!new)
        return(NULL);
    new->value = ft_strdup(value);
    new->next = NULL;
    return (new);
}

t_env   *find_last_env(t_env *head)
{
    t_env	*temp;

	temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	append_env(t_env **list, t_env *new)
{
	t_env	*temp;

	if (*list)
	{
		temp = find_last_env(*list);
		temp->next = new;
		new->next = NULL;
	}
	else
	{
		*list = new;
		(*list)->next = NULL;
	}
}

