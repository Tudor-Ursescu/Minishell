/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:33:35 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/28 11:56:28 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_tokens(t_token **list)
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
	*list = NULL;
}

void	free_cmds(t_cmd *list)
{
	t_cmd	*temp;

	while (list)
	{
		free_tokens(&list->redirections);
		free_matrix(list->args);
		temp = list->next;
		free(list);
		list = temp;
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
	*list = NULL;
}

void	free_matrix(char **args)
{
	int	i;

	if (args == NULL)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	args = NULL;
}

void	free_all(t_data *data)
{
	free_cmds(data->cmd_list);
	free_tokens(&data->token_list);
	free(data->line);
	unlink_heredocfiles(data);
}
