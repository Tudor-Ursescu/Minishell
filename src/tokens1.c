/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:40:33 by tursescu          #+#    #+#             */
/*   Updated: 2025/03/21 10:21:07 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

t_token	*create_token(t_token_types type, const char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		printf("Token allocation errror\n");
		return (NULL);
	}
	new->type = type;
	new->value = ft_strdup(value);
	new->append = 0;
	new->next = NULL;
	return (new);
}

t_token	*find_last_token(t_token *head)
{
	t_token	*temp;

	temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	append_token(t_token **list, t_token *new)
{
	t_token	*temp;

	if (*list)
	{
		temp = find_last_token(*list);
		temp->next = new;
	}
	else
	{
		*list = new;
		(*list)->next = NULL;
	}
}

int	is_redirection(t_token *token)
{
	return (token->type == T_IN || token->type == T_OUT
		|| token->type == T_HEREDOC || token->type == T_APPEND);
}

int	is_pipe(t_token *token)
{
	return (token->type == T_PIPE);
}
