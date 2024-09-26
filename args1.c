/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:40:33 by tursescu          #+#    #+#             */
/*   Updated: 2024/09/26 12:15:02 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_args	*create_arg(t_token_types type, const char *value)
{
	t_args *new;
	
	new = malloc(sizeof(t_args));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	prepend_arg(t_args **list, t_args *new)
{
	new->next = *list;
	*list = new;
}

t_args	*find_last_arg(t_args *head)
{
	t_args *temp;
	
	temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	append_arg(t_args **list, t_args *new)
{
	t_args *temp;
	
	if (*list)
	{
		temp = find_last_arg(*list);
		temp->next = new;
		new->next = NULL;//don't know if i need this
	}
	else
	{
		*list = new;
		(*list)->next = NULL;	
	}
}

void free_args(t_args **list)
{
	t_args	*temp;
	t_args	*head;

	head = *list;
	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}