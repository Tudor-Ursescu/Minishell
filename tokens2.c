/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:07:28 by tursescu          #+#    #+#             */
/*   Updated: 2024/09/27 16:43:56 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	list_len(t_token *head)
{
	t_token *temp;
	size_t i;

	temp = head;
	i = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

bool is_redirection(t_token *token)
{
	return (token->type == T_IN || token->type == T_OUT ||
			token->type == T_HEREDOC || token->type == T_APPEND);
}

bool is_pippe(t_token *token)
{
	return (token->type = T_PIPE);
}

