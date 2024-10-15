/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:00:39 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/15 14:52:16 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd	*create_cmd_list(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*last_cmd;
	t_cmd	*curr_cmd;
	t_token	*curr_tokens;
	
	cmd_list = NULL;
	last_cmd = NULL;
	curr_tokens = tokens;
	while (curr_tokens != NULL)
	{
		curr_cmd = malloc(sizeof(t_cmd));
		if (!curr_cmd)
		{
			printf("Memory alloc failed for command\n");
			free_cmds(cmd_list);
			return (NULL);
		}
		curr_cmd->redirections = get_redirectons(curr_tokens);
		curr_cmd->args = get_args(curr_tokens);
		if (curr_cmd->args == NULL)
		{
			printf("Command creation failed!\n");
			free(curr_cmd);
			free_cmds(cmd_list);
			return (NULL);
		}
		curr_cmd->next = NULL;
		if (!cmd_list) {
			cmd_list = curr_cmd;
			last_cmd = curr_cmd;
		}
		else
		{
			last_cmd->next = curr_cmd;
			last_cmd = curr_cmd;
		}
		curr_tokens = find_next_cmd(curr_tokens);
	}
	return (cmd_list);
}
