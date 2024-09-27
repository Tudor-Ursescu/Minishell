/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:33:35 by tursescu          #+#    #+#             */
/*   Updated: 2024/09/27 16:04:10 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void free_tokens(t_token **list)
{
	t_token	*temp;
	t_token	*head;

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

void free_cmds(t_cmd *head)
{
    t_cmd   *temp;

    while (head)
    {
        free_tokens(head->redirect);
        free_matrix(head->args);
        temp = head->next;
        free(head);
        head = temp;
    }
}

void	free_env(t_env **list)
{
	t_env	*temp;
	t_env	*head;

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

void    free_all(t_cmd *cmd_list, t_token *token_list)
{
    free_cmds(cmd_list);
    free_tokens(cmd_list);
}