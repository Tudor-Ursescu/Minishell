/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:40:33 by tursescu          #+#    #+#             */
/*   Updated: 2024/09/27 16:34:07 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*create_token(t_token_types type, const char *value)
{
	t_token *new;
	
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL); //ERROR needed
	new->type = type;
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	prepend_token(t_token **list, t_token *new)
{
	new->next = *list;
	*list = new;
}

t_token	*find_last_token(t_token *head)
{
	t_token *temp;
	
	temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	append_token(t_token **list, t_token *new)
{
	t_token *temp;
	
	if (*list)
	{
		temp = find_last_token(*list);
		temp->next = new;
		new->next = NULL;//don't know if i need this
	}
	else
	{
		*list = new;
		(*list)->next = NULL;	
	}
}

void print_token_list(t_token *head)
{
	t_token *temp;

	temp = head;
	while (temp)
	{
		printf("Token:%s, Type:%d\n", temp->value, temp->type);
		temp = temp->next;
	}
}